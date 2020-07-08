#include <iostream>
#include "population.h"

using namespace std;

int main(){
	const int ncities=32;
	Cities c1("../Es_lezione_09/cities_in_circle.dat", ncities);
	Cities c2("../Es_lezione_09/cities_in_square.dat", ncities);
	ofstream fout;
	Random gen;

	int seed[4];
	int p1, p2;
	ifstream Primes("../Random_generator/Primes");
 	if (Primes.is_open()){
 		Primes >> p1 >> p2 ;
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("../Random_generator/seed.in");
	string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				gen.SetRandom(seed,p1,p2);
			}
		}
	input.close();
	} 
	else cerr << "PROBLEM: Unable to open seed.in" << endl;

	item e1(c1), e2(c2);

	const int nbeta=2000, nsteps=300;
	const double p=30.;
	const double xi_min=pow(1E-3, 1./p), xi_max=pow(1E3, 1./p), deltaxi=(xi_max-xi_min)/double(nbeta);

	cout << endl << "\t--------------------- Running simulated annealing ---------------------" << endl;
	cout << "\t\t\t    Temperature from " << 1./(pow(xi_min, p)) << " to " << 1./(pow(xi_max, p)) << endl;

	double xi=xi_min-deltaxi;
	for(double i=0; i<nbeta; i++){
		xi+=deltaxi;
		double beta=pow(xi, p);
		cout << " --------- Step #" << i+1 << " --- Temperature = " << 1./beta << "  ------------ " << endl;
		e1.Set_Params(beta, nsteps);
		e1.Simulated_Annealing(c1, gen);

		e2.Set_Params(beta, nsteps);
		e2.Simulated_Annealing(c2, gen);

		fout.open("path_length_circle.dat", ios::app);
		fout << e1.GetL1() << endl;
		fout.close();
		fout.open("path_length_square.dat", ios::app);
		fout << e2.GetL1() << endl;
		fout.close();
	}

	// Printing to file
	fout.open("path_circle.dat");
	e1.PrintPath(fout);
	fout.close();

	fout.open("path_square.dat");
	e2.PrintPath(fout);
	fout.close();


return 0;
}
