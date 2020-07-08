#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "Random_generator/random.h"
#include "functions.h"
#include "blocking_method.h"


int main(){
	// market parameters
	const double S0=100.;
	const double T=1.;
	const double K=100.;
	const double r=0.1;
	const double sigma=0.25;

	// simulation parameters
	const unsigned int M=1E5;	// # of simulations
	const unsigned int N=1E2;	// # of blocks
	const unsigned int L=M/N;

	const unsigned int D=1E2;	// # of sub-invervals for discrete simulation
	const double h=T/D;		// step of discrete simulation

	Random gen;

		// simulation via direct calculation
	double aveC_ex[N], ave2C_ex[N], aveC_prog_ex[N], errC_ex[N], sumC1=0.;
	double aveP_ex[N], ave2P_ex[N], aveP_prog_ex[N], errP_ex[N], sumP1=0.;

	for(unsigned int i=0; i<M; i++){
		double S1=S0*exp((r-0.5*sigma*sigma)*T+sigma*sqrt(T)*gen.Gauss(0., 1.));
		sumC1+=exp(-r*T)*max(0., S1-K);
		sumP1+=exp(-r*T)*max(0., K-S1);

		check(L, i+1, aveC_ex, ave2C_ex, &sumC1);
		check(L, i+1, aveP_ex, ave2P_ex, &sumP1);
	}

	Blocking_Method(N, aveC_ex, ave2C_ex, aveC_prog_ex, errC_ex);
	Blocking_Method(N, aveP_ex, ave2P_ex, aveP_prog_ex, errP_ex);


		// simulation via discrete steps
	double aveC_dis[N], ave2C_dis[N], aveC_prog_dis[N], errC_dis[N], sumC2=0.;
	double aveP_dis[N], ave2P_dis[N], aveP_prog_dis[N], errP_dis[N], sumP2=0.;

	for(unsigned int i=0; i<M; i++){
		double S2=S0;
		for(unsigned int j=0; j<D; j++)
			S2*=exp((r-0.5*sigma*sigma)*h+sigma*sqrt(h)*gen.Gauss(0., 1.));

		sumC2+=exp(-r*T)*max(0., S2-K);
		sumP2+=exp(-r*T)*max(0., K-S2);

		check(L, i+1, aveC_dis, ave2C_dis, &sumC2);
		check(L, i+1, aveP_dis, ave2P_dis, &sumP2);
	}
	Blocking_Method(N, aveC_dis, ave2C_dis, aveC_prog_dis, errC_dis);
	Blocking_Method(N, aveP_dis, ave2P_dis, aveP_prog_dis, errP_dis);
	
	// printing onto file
	ofstream fout;
	fout.open("dataEx03_1.dat");
	fout << M << setw(20) << N;
	for(unsigned int i=1; i<N; i++)
		fout << endl << aveC_prog_ex[i] << setw(15) << aveP_prog_ex[i] << setw(15) << aveC_prog_dis[i] << setw(15) << aveP_prog_dis[i] << setw(15) << errC_ex[i] << setw(15) << errP_ex[i] << setw(15) << errC_dis[i] << setw(15) << errP_dis[i];

	fout.close();

return 0;
}
