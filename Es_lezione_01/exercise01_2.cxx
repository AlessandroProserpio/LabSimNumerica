#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include "Random_generator/random.h"

using namespace std;

int main(){
	
	const unsigned int N[4]={1, 2, 10, 100};
	const unsigned int n=1E4;
	ofstream fout;
	Random gen;

	const double min=1., max=6.;		// standard dice parameters
	const double lambda=1.;			// exponential dice parameters
	const double Gamma=1., mu=0.;		// lorentzian dice parameters

	fout.open("dataEx2.dat");

	for(unsigned int i=0; i<n; i++){
		double s1=0., s2=0., s3=0.;
		unsigned int k=0;
	
		for(unsigned int j=0; j<N[3]; j++){
			double rand=gen.Rannyu();
			s1+=min+(max-min)*rand;
			s2+=-log(1-rand)/lambda;
			s3+=mu+Gamma*tan(M_PI*(rand-0.5));
	
			if(j+1==N[k]){
				fout << s1/(1.*N[k]) << setw(20) << s2/(1.*N[k]) << setw(20) << s3/(1.*N[k]) << setw(20);
				k++;
			}
		}
		fout << endl;		
	}

	fout.close();

return 0;
}
