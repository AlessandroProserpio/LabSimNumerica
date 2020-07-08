#include "mpi.h"
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
#include <random>
#include "population.h"

using namespace std;

int main(int argc, char* argv[]){
	int size, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Random gen;	
	int seed[4];
	int p1, p2;
	ifstream Primes("Random_generator/Primes");
 	if (Primes.is_open()){
		int k=0;
		do{
 			Primes >> p1 >> p2 ;
			k++;
		}while(k<=rank);
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("Random_generator/seed.in");
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


	const int Nmigr=40;
	const int ncities=32;
	const int npop=150;
	const int ngen=1000;
	Cities c("../Es_lezione_09/cities_in_square.dat", ncities);
	vector<item> pop;
	
	item i0(c);
	pop.push_back(i0);

	for(int i=1; i<npop; i++){
		int k=gen.Discrete_Unif(1, ncities-1, 1), m=gen.Discrete_Unif(1, ncities-1, 1);
		item I(pop[i-1], k, m, c);
		pop.push_back(I);
	}
	sort(pop.begin(), pop.end(), sortcryteria::sort_by_L1);
	//sort(pop.begin(), pop.end(), sortcryteria::sort_by_L2);

	ofstream Pop;
	ostringstream supp;
	supp << rank+1 << ".dat";

	default_random_engine e(0);
	MPI_Status stat1, stat2;
	MPI_Request req1, req2;

	double tstart=MPI_Wtime();

	vector<int> v;
	for(int s=0; s<size; s++)
		v.push_back(s);
	
	if(rank==0) cout << endl << "--------- Starting simulation --------------" << endl;

	for(int j=0; j<ngen; j++){
		if((j+1)%100==0)
		cout << rank << "\t Generation " << j+1 << endl;

		vector<item> newpop;

		for(int s=0; s<npop; s++){
			int i_father=int(npop*pow(gen.Rannyu(0,1), q));
			item father(pop[i_father], c);
			int i_mother=int(npop*pow(gen.Rannyu(0,1), q));
			item mother(pop[i_mother], c);

			// Mutations
			father.Mutate(c, gen);
			mother.Mutate(c, gen);
			// Crossover
			if(gen.Rannyu() < pc){
				int cut=gen.Discrete_Unif(1, father.GetSize()-1, 1);
				vector<int> appo=father.Crossover(cut, mother.GetPerson(), c);
				mother.Crossover(cut, appo, c);
			}
			newpop.push_back(father);
			newpop.push_back(mother);
		}
		if(newpop.size() > npop)
			newpop.pop_back();
	
		pop=newpop;	
		sort(pop.begin(), pop.end(), sortcryteria::sort_by_L1);
		//sort(pop.begin(), pop.end(), sortcryteria::sort_by_L2);

		if((j+1)%Nmigr==0 and j+1!=ngen){

			shuffle(v.begin(), v.end(), e);

			for(int s=0; s<size; s+=2){
				if(rank==v[s]){	
					vector<int> tosend=pop[0].GetPerson();
					vector<int> receiver(ncities);

					MPI_Isend(&tosend[0], ncities, MPI_INTEGER, v[s+1], v[s], MPI_COMM_WORLD, &req1);
					MPI_Recv(&receiver[0], ncities, MPI_INTEGER, v[s+1], v[s+1], MPI_COMM_WORLD, &stat2);
					
					item I(receiver, c);
					pop[0]=I;
				}
		
				else if(rank==v[s+1]){
					vector<int> tosend=pop[0].GetPerson();
					vector<int> receiver(ncities);

					MPI_Send(&tosend[0], ncities, MPI_INTEGER, v[s], v[s+1], MPI_COMM_WORLD);
					MPI_Recv(&receiver[0], ncities, MPI_INTEGER, v[s], v[s], MPI_COMM_WORLD, &stat1);

					item I(receiver, c);
					pop[0]=I;
				}
			}

			sort(pop.begin(), pop.end(), sortcryteria::sort_by_L1);
			//sort(pop.begin(), pop.end(), sortcryteria::sort_by_L2);
			if(rank==0){
				cout << "Migration executed: ";
				for(int s=0; s<size; s+=2)
					cout << v[s] << " to " << v[s+1] << " \t ";
				cout << endl;
			}
		}

		string filename1="MPI_L1_";
		filename1.append(supp.str());
		Pop.open(filename1, ios::app);
		Pop << pop[0].GetL1() << endl;
		Pop.close();
	}		


	double tend=MPI_Wtime();

	cout << "I am " << rank << " \t time = " << tend-tstart << endl; 

	if(rank==0) cout << endl << "PRINTING ONTO FILE" << endl;
	string filename2="MPI_square_best_path";
	filename2.append(supp.str());
	Pop.open(filename2);
	for(int l=0; l<ncities; l++)
		Pop << pop[0][l] << setw(5);
	Pop << endl << pop[0].GetL1();
	Pop.close();

	MPI_Finalize();

return 0;
}
