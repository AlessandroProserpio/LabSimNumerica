#include "multidimfunctions.h"

double HAtom_1s::operator()(vector<double> x) const{
	double r=0.;
	for(unsigned int i=0; i<x.size(); i++)
		r+=x[i]*x[i];

	return exp(-2*sqrt(r))/M_PI;
}

double HAtom_2pz::operator()(vector<double> x) const{
	double r=0.;
	for(unsigned int i=0; i<x.size(); i++)
		r+=x[i]*x[i];

	return 1./(8*M_PI)*x[2]*x[2]*exp(-sqrt(r));
}
