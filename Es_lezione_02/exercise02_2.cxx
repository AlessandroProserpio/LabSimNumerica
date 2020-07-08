#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include "blocking_method.h"
#include "Random_generator/random.h"
#include "posizione.h"
#include "RW.h"

int main(){
	const unsigned int M=1E4;			// # of RWs
	const unsigned int S=1E2;			// steps in each RW
	const unsigned int N=1E2;			// number of blocks
	const unsigned int L=M/N;			// size of a block
	const double a=1.;				// lattice constant
	Posizione x0(0., 0., 0.);			// starting position of the walker
	Random_Walk3D RW1(x0, S, a), RW2(x0, S, a);
	ofstream fout;

	double ave[S], ave2[S], err[S], norm2[S];
	double aveC[S], ave2C[S], errC[S], norm2C[S];

	set_to_zero(norm2, S);
	set_to_zero(norm2C, S);
	set_to_zero(ave, S);
	set_to_zero(ave2, S);
	set_to_zero(aveC, S);
	set_to_zero(ave2C, S);

	for(unsigned int i=0; i<M; i++){
		RW1.Set_Start(x0);
		RW2.Set_Start(x0);
		RW1.Cubic_Lattice();
		RW2.Isotropic_Space();

		for(unsigned int k=0; k<S; k++){
	// the k-th component of norm2 is the sum of squared norm of the points where the walker lies after k steps in each simulation
			norm2[k]+=RW1.Get_distance()[k];
			norm2C[k]+=RW2.Get_distance()[k];
		}

		if((i+1)%L==0){
			for(unsigned int k=0; k<S; k++){
// the k-th component of ave is the average over all the M simulations of the squared distance from the origin of the walker after k steps 
				ave[k]+=norm2[k]/M;
				aveC[k]+=norm2C[k]/M;	
	// the k-th component of ave2 is the sum of the averages over a single block of the double-squared distance at the k-th step
				ave2[k]+=pow(norm2[k]/L, 2);	
				ave2C[k]+=pow(norm2C[k]/L, 2);
			}
			
			set_to_zero(norm2, S);
			set_to_zero(norm2C, S);
		}	
	}

	for(unsigned int i=0; i<S; i++){
		err[i]=sqrt((ave2[i]-pow(ave[i], 2))/N);
		errC[i]=sqrt((ave2C[i]-pow(aveC[i], 2))/N);
	}
	

		/// Printing onto file ///	
	fout.open("dataEx2_2.dat");
	fout << S << endl;

	for(unsigned int i=1; i<N; i++)
		fout << sqrt(ave[i]) << setw(15) << sqrt(aveC[i]) << setw(15) << err[i]/(2*sqrt(ave[i])) << setw(15) << errC[i]/(2*sqrt(ave[i])) << endl; 	// error on the sqrt(r^2) is evaluated from the error on r^2 with propagation of uncertainty

	fout.close();

return 0;
}
