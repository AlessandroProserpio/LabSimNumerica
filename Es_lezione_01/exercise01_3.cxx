#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include "Random_generator/random.h"
#include "blocking_method.h"

using namespace std;

double Generate_sine(Random * gen);		// generates an angle in (0, 2\pi) uniformly (without using \pi, as described in the 								notebook) and returns its sine

int main(){
	const unsigned int M=1E6;		// size of the sample
	const unsigned int N=1E2;		// # of blocks
	const unsigned int L=M/N;		// size of a block
	const double l=5.;			// length of the needle (in cm)
	const double d=8.;			// spacing of the lines (in cm)
	Random gen;				// pseudo-random numbers generator
	ofstream fout;				// stream for output file(s)

	unsigned int N_hit=0;
	double ave[N], ave2[N], ave_prog[N], err[N];

	for(unsigned int i=0; i<M; i++){
		double y=gen.Rannyu(0., d);
		double sinphi=Generate_sine(&gen);

		if(y+l*sinphi<0 or y+l*sinphi>d)
			N_hit++;

		if((i+1)%L==0){
			unsigned int k=(i+1)/L-1;
			ave[k]=2.*l*L/(N_hit*d);
			ave2[k]=ave[k]*ave[k];
			N_hit=0;
		}
	}

	Blocking_Method(N, ave, ave2, ave_prog, err);

	// Printing onto file
	fout.open("dataEx3.dat");

	fout << M << setw(20) << N << endl;
	
	for(unsigned int i=1; i<N; i++)
		fout << ave_prog[i]-M_PI << setw(20) << err[i] << endl;

return 0;
}

double Generate_sine(Random* gen){
	double xi, eta;
	do{
		xi=gen->Rannyu(-1., 1.);
		eta=gen->Rannyu(-1., 1.);	
	}while(sqrt(xi*xi+eta*eta)>1);

	return eta/sqrt(xi*xi+eta*eta);	
}
