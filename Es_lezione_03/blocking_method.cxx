#include "blocking_method.h"

double error(double* av, double* av2, unsigned int N){
	if(N==0)
		return 0;

	return sqrt((av2[N]-av[N]*av[N])/N);

}

void set_to_zero(double* v, unsigned int dim){
	for(unsigned int i=0; i<dim; i++)
		v[i]=0.;
}

void set_to_zero(int * N, unsigned int dim){
	for(unsigned int i=0; i<dim; i++)
		N[i]=0;
}

void check(unsigned int L, unsigned int i, double* ave, double* ave2, double* sum){
	if(i%L==0){
		ave[i/L-1]=(*sum)/L;
		ave2[i/L-1]=ave[i/L-1]*ave[i/L-1];		
		*sum=0.;
	}
}

void Blocking_Method(unsigned int N, double* ave, double* ave2, double* ave_prog, double* err){

	double ave_prog2[N];
	set_to_zero(ave_prog, N);
	set_to_zero(ave_prog2, N);

	for(unsigned int i=0; i<N; i++){
		for(unsigned int j=0; j<i+1; j++){
			// calculating progressive averages
			ave_prog[i]+=ave[j];
			ave_prog2[i]+=ave2[j];
		}
		ave_prog[i]/=i+1.;
		ave_prog2[i]/=i+1.;
		err[i]=error(ave_prog, ave_prog2, i);
	}
}
