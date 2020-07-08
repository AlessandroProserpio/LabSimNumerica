#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "Random_generator/random.h"
#include "blocking_method.h"

using namespace std;

int main(){
	Random gen;
	unsigned int M=1E4;			// number of steps
	const unsigned int N=1E2; 		// number of blocks
	unsigned int L=M/N;
	ofstream fout;

	double delta=5.;	
	unsigned int accept=0;			// counter for the accepted moves
	double x=0.;				// starting position for integral evaluation
	double sum=0.;
	double mu=0.8, sigma=0.65;		// starting configuration for simulated annealing
	function* Psi1=new PsiT(mu, sigma);
	function* HPsi1=new HPsiT(mu, sigma);

	// simulated annealing
	unsigned int nbeta=50, nsteps=300;
	double p=25.;
	double xi_min=pow(0.002, 1./p), xi_max=pow(2E3, 1./p), delta_xi=(xi_max-xi_min)/(double)(nbeta);
	double s=0.1, oldE=0.;

	// GS wavefunction histogram	
	int nbins=100;
	double histo[nbins];
	double min=-3., max=3., step=(max-min)/(double)nbins;

	// blocking method
	double ave[N], ave_2[N], ave_prog[N], err[N];
	double aveh[nbins][N], ave_2h[nbins][N], ave_progh[nbins][N], errh[nbins][N];

	set_to_zero(histo, nbins);

	cout << endl << "\t--------------------- Running simulated annealing ---------------------" << endl;
	cout << "\t\t\t    Temperature from " << 1./(pow(xi_min, p)) << " to " << 1./(pow(xi_max, p)) << endl;

	for(int i=0; i<M; i++){
		x=gen.Metropolis_Step(Psi1, 'U', x, delta, &accept);
		oldE+=(*HPsi1)(x)/(*Psi1)(x);
	}

	oldE/=(double)M;

	double xi=xi_min-delta_xi;
	for(int j=1; j<=nbeta; j++){
		xi+=delta_xi;
		double beta=pow(xi, p);
		cout << " --------- Temperature = " << 1./beta << "  ------------ " << endl;
		for(int i=1; i<=nsteps; i++){
			// generate mutrial and sigmatrial from normal distribution centered in the previous values
			double mutrial=gen.Rannyu(mu-0.5*s, mu+0.5*s);
			double sigmatrial=gen.Rannyu(sigma-0.5*s, sigma+0.5*s);

			Psi1->SetParameter('m', mutrial);
			HPsi1->SetParameter('m', mutrial);
			Psi1->SetParameter('s', sigmatrial);
			HPsi1->SetParameter('s', sigmatrial);
			x=0.;
			accept=0;
			sum=0.;
			// evaluate the energy for the chosen sigma and mu (trial)
			for(unsigned int k=0; k<M; k++){
				x=gen.Metropolis_Step(Psi1, 'U', x, delta, &accept);
				sum+=(*HPsi1)(x)/(*Psi1)(x);
			}

			sum/=(double)M;

			// acceptance
			double A=exp( -beta*( sum - oldE ) );

			if(A>gen.Rannyu()){
				oldE=sum;
				mu=mutrial;
				sigma=sigmatrial;
			}

			else{
				Psi1->SetParameter('m', mu);
				HPsi1->SetParameter('m', mu);
				Psi1->SetParameter('s', sigma);
				HPsi1->SetParameter('s', sigma);
			}
		}
	}

	cout << endl << "\t----------- Simulated annealing terminated --------------" << endl;
	cout << "Minimum find at:" << endl << "\t mu = " << Psi1->GetParameter('m') << endl << "\t sigma = " << Psi1->GetParameter('s') << endl;

	// evaluating energy and GS wavefunction
	cout << endl << "Calculating energy and GS wavefunction" << endl;

	M=1E7;
	L=M/N;

	x=0.;
	accept=0;
	sum=0.;

	for(int i=0; i<M; i++){
		x=gen.Metropolis_Step(Psi1, 'U', x, delta, &accept);
		sum+=(*HPsi1)(x)/(*Psi1)(x);

		if(x<max and x>min)
			histo[int((x-min)/step)]++;

		check(L, i+1, ave, ave_2, &sum);
		for(unsigned int r=0; r<nbins; r++)
			check(L, i+1, aveh[r], ave_2h[r], histo+r);
	}

	Blocking_Method(N, ave, ave_2, ave_prog, err);
	for(unsigned int j=0; j<nbins; j++)
		Blocking_Method(N, aveh[j], ave_2h[j], ave_progh[j], errh[j]);

	cout << endl << "E_0 = " << ave[N-1] << " +/- " << err[N-1];
	cout << endl << "Acceptance percentage = " << 1E2*accept/M << endl;


	// Printing results onto file
	int wd=20;
	fout.open("dataEx08_1.dat");

	fout << M << setw(wd) << N << endl;
	fout << Psi1->GetParameter('m') << setw(wd) << Psi1->GetParameter('s') << endl;

	for(unsigned int i=1; i<N; i++)
		fout << ave_prog[i] << setw(wd) << err[i] << endl;

	fout.close();

	fout.open("PsiT_sq_mod.dat");

	fout << min << setw(wd) << max << setw(wd) << nbins << endl;
	for(int i=0; i<nbins; i++)
		fout << min+(i+0.5)*step << setw(wd) << ave_progh[i][N-1] << setw(wd) << errh[i][N-1] << endl;

	fout.close();
return 0;
}
