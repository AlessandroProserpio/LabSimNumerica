#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Random_generator/random.h"
#include "blocking_method.h"

using namespace std;

int main(){
	const unsigned int M=1E6;		// size of the sample
	const unsigned int N=1E2;		// # of blocks
	const unsigned int L=M/N;		// size of a block
	Random gen;				// pseudo-random numbers generator
	ofstream fout;				// stream for output file(s)

	////// Points #1 and #2 ////////////////////////////////////////////////////////////
	double ave[N], ave2[N], ave_prog[N], err[N], sum=0.;
	double avevar[N], ave2var[N], ave_prog_var[N], err_var[N], sumvar=0.;
	
	for(unsigned int i=0; i<M; i++){
		double rand=gen.Rannyu();
		sum+=rand;
		sumvar+=(rand-0.5)*(rand-0.5);

		check(L, i+1, ave, ave2, &sum);
		check(L, i+1, avevar, ave2var, &sumvar);
	}

	Blocking_Method(N, ave, ave2, ave_prog, err);
	Blocking_Method(N, avevar, ave2var, ave_prog_var, err_var);

	// Writing results onto file
	fout.open("dataEx1_1.dat");

	fout << M << setw(20) << N <<endl;
	for(unsigned int i=1; i<N; i++)
		fout << ave_prog[i]-0.5 <<  setw(20)  << ave_prog_var[i]-1/12. << setw(20) << err[i] << setw(20) << err_var[i] << endl;

	fout.close();

	/////////// Point #3 /////////////////////////////////////////

	const unsigned int n=1E4;	// # of events per simulation
	int N_hit[N];			// counter for the number of events per sub-interval
	double h=1./N, avn=n*h;		// amplitude of each sub-interval & expected value for average events per sub-interval
	double chi2[N];
	vector<double> sample;

	set_to_zero(chi2, N);

	for(unsigned int i=0; i<N; i++){
		for(unsigned int j=0; j<n; j++)
			sample.push_back(gen.Rannyu()); 	// generation of n points from Unif(0,1)

		sort(sample.begin(), sample.end());		// sorting the vector makes counting points in each subinterval easier
		unsigned int k=0;
		set_to_zero(N_hit, N);			
		for(unsigned int j=0; j<N; j++){
			// counting # of points in each subinterval
			while(sample[k]<(j+1.)*h and k<n){
				N_hit[j]++;
				k++;				
			}
		}

		for(unsigned int l=0; l<N; l++)
			chi2[i]+=(N_hit[l]-avn)*(N_hit[l]-avn)/(avn);

		sample.clear();
	}

	// Writing data onto file
	fout.open("dataEx1_2.dat");
	for(unsigned int i=0; i<N; i++)
		fout << chi2[i] << endl;

	fout.close();


return 0;
}
