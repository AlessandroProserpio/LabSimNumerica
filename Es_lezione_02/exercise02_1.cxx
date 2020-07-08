#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "importance_sampling.h"
#include "functions.h"

using namespace std;

int main(){

	const unsigned int M=1E6;				// # of throws
	const unsigned int N=1E2;				// # of blocks
	ofstream fout;	
	function* f=new cosine(M_PI*0.5, M_PI*0.5, 0., 0.);
	Importance_Sampling* unif=new IS_Uniform(0., 1.);
	Importance_Sampling* lin=new IS_Linear(0., 1., -1., 1.);

	unif->Run(f, M, N);
	lin->Run(f, M, N);
	
	/// writing onto file
	fout.open("dataEx2_1.dat");

	fout << M << setw(20) << N << endl;

	for(unsigned int i=1; i<N; i++)
		fout << unif->Get_Estimate_Prog()[i]-1. << setw(20) << lin->Get_Estimate_Prog()[i]-1. << setw(20) << unif->Get_Error_Prog()[i] << setw(20) << lin->Get_Error_Prog()[i] << endl;


return 0;
}
