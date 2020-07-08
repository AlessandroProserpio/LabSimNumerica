#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "Random_generator/random.h"
#include "blocking_method.h"
#include "posizione.h"

using namespace std;

int main(){
	Random gen;
	unsigned int M=1E6;		// number of steps
	unsigned int N=1E2; 		// number of blocks
	unsigned int L=M/N;
	ofstream fout;

	double delta1[2]={2.3, 0.75}, delta2[2]={5.1, 1.8};	
	// deltai[0]: length of the edge of the cube for the uniform extraction in Metropolis algorithm for Psi_i
	// deltai[1]: variance of normal distribution in Metropolis algorithm for Psi_i
	char distr[2]={'U', 'G'};			// 'U' for uniform and 'G' for normal
	unsigned int accept1=0, accept2=0;		// counter for the accepted moves
	Posizione x1, x2;			
	double sum1=0., sum2=0.;

	Multi_Dim_Function* Psi1=new HAtom_1s;
	Multi_Dim_Function* Psi2=new HAtom_2pz;

	double ave1[2][N], ave1_2[2][N], ave1_prog[2][N], err1[2][N];
	double ave2[2][N], ave2_2[2][N], ave2_prog[2][N], err2[2][N];

	//fout.open("dataEx05_1_far.dat");
	for(unsigned int j=0; j<2; j++){
		sum1=0.;
		sum2=0.;
		accept1=0;
		accept2=0;
		x1.SetXYZ(100., 100., 100.);			// starting point for Psi1 Metropolis Algorithm
		x2.SetXYZ(100., 100., 100.);			// starting point for Psi2 Metropolis Algorithm
		for(unsigned int i=0; i<M; i++){
			x1=gen.Metropolis_Step(Psi1, distr[j], x1, delta1[j], &accept1);
			x2=gen.Metropolis_Step(Psi2, distr[j], x2, delta2[j], &accept2);

			if((i+1)%200==0){
			// Printing 1E4 points to file to get 3d orbital "picture"
				fout.open("1s-orbital.dat", ios::app);
				fout << x1.GetX() << setw(20) << x1.GetY() << setw(20) << x1.GetZ() << endl;
				fout.close();

				fout.open("2pz-orbital.dat", ios::app);
				fout << x2.GetX() << setw(20) << x2.GetY() << setw(20) << x2.GetZ() << endl;
				fout.close();	
			}

			sum1+=x1.GetR();
			sum2+=x2.GetR();
			/*if(j==1)
				fout << x1.GetR() << setw(15) << x2.GetR() << endl;*/

			check(L, i+1, ave1[j], ave1_2[j], &sum1);
			check(L, i+1, ave2[j], ave2_2[j], &sum2);

		}
		cout << endl << "Acceptance percentage" << endl << " Psi1 " << setw(18) << " Psi2 ";
		cout << endl << (1E2*accept1)/M << " %" << setw(15) << (1E2*accept2)/M << " %" << endl;
	}

	//fout.close();
	for(unsigned int j=0; j<2; j++){
		Blocking_Method(N, ave1[j], ave1_2[j], ave1_prog[j], err1[j]);
		Blocking_Method(N, ave2[j], ave2_2[j], ave2_prog[j], err2[j]);
	}

	// Printing results onto file
	fout.open("dataEx05_1_far.dat");

	fout << M << setw(20) << N << endl;

	for(unsigned int i=1; i<N; i++){
		for(unsigned int j=0; j<2; j++)
			fout << ave1_prog[j][i] << setw(15) << ave2_prog[j][i] << setw(15);
		for(unsigned int j=0; j<2; j++)
			fout << err1[j][i] << setw(15) << err2[j][i] << setw(15);
		
		fout << endl;	
	}


return 0;
}
