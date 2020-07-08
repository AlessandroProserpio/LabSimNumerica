#include "functions.h"

double max(double a, double b){
	if(a>b)
		return a;
	
	return b;
}

	//////////////// Elementary Functions of Real Analysis /////////////////////////

cosine::cosine(double a, double b, double c, double d){
	m_a=a;
	m_b=b;
	m_c=c;
	m_d=d;
}

void cosine::SetParameter(char c, double x){
	switch(c){
		case 'a':
			m_a=x;
			break;
		case 'b':
			m_b=x;
			break;
		case 'c':
			m_c=x;
			break;
		case 'd':
			m_d=x;
			break;
		default:
			cerr << endl << "First input must be chosen between 'a', 'b', 'c' or 'd' as in: f(x)=a*cos(b*x+c)+d" << endl;
			break;
	}
}

double cosine::GetParameter(char c) const{
	switch(c){
		case 'a':
			return m_a;
		case 'b':
			return m_b;
		case 'c':
			return m_c;
		case 'd':
			return m_d;
		default:
			cerr << endl << "Input must be chosen between 'a', 'b', 'c' or 'd' as in: f(x)=a*cos(b*x+c)+d"<< endl;
			return -1;
	}
}


		////////////////// Probability density functions ////////////////////////////////
void uniform_1d::SetParameter(char c, double p){
	switch(c){
		case 'a':
			m_a=p;
			break;
		case 'b': 
			m_b=p;
			break;
		default:
			cerr << endl << "First input MUST be either 'a' or 'b' as in: f(x)=1/(b-a)" << endl;
			break;
	}
}
double uniform_1d::GetParameter(char c) const{
	switch(c){
		case 'a':
			return m_a;
		case 'b': 
			return m_b;
		default:
			cerr << endl << "Input MUST be either 'a' or 'b' as in: f(x)=1/(b-a)" << endl;
			return -1;
	}
}
void gauss::SetParameter(char c, double p){
	switch(c){
		case 'm':
			m_mu=p;
			break;
		case 's': 
			m_sigma=p;
			break;
		default:
			cerr << endl << "First input MUST be either 'm' or 's' as in: f(x)=exp(-0.5*((x-m)/s)^2)" << endl;
			break;
	}
}
double gauss::GetParameter(char c) const{
	switch(c){
		case 'm':
			return m_mu;
		case 's': 
			return m_sigma;
		default:
			cerr << endl << "Input MUST be either 'm' or 's' as in: f(x)=exp(-0.5*((x-m)/s)^2)" << endl;
			return -1;
	}
}

void exp_distr::SetParameter(char c, double p){
	m_lambda=p;
}
double exp_distr::GetParameter(char c) const{
	return m_lambda;
}

void cauchy_lorentz::SetParameter(char c, double p){
	switch(c){
		case 'm':
			m_mu=p;
			break;
		case 'G': 
			m_Gamma=p;
			break;
		default:
			cerr << endl << "First input MUST be either 'm' or 'G' as in: f(x)=1/((x-m)^2+G^2)" << endl;
			break;
	}
}
double cauchy_lorentz::GetParameter(char c) const{
	switch(c){
		case 'm':
			return m_mu;
		case 'G': 
			return m_Gamma;
		default:
			cerr << endl << "Input MUST be either 'm' or 'G' as in: f(x)=1/((x-m)^2+G^2)" << endl;
			return -1;
	}
}

linear::linear(double a, double b, double m, double q){
	if(m==0){
		cerr << endl << "For a uniform distribution use class 'uniform_1d'";
		m_a=m_b=m_q=0.;
		m_N=m_M=1.;
		cerr << endl << "To re-set parameters with legit values use method SetParameter(char, double)";
	}
	else if(m*a+q<0. or m*b+q<0.){
		cerr << endl << "PDF is not positively-defined on the given interval, setting all parameters to 0";
		m_a=m_b=m_q=0.;
		m_N=m_M=1.;
		cerr << endl << "To re-set parameters with legit values use method SetParameter(char, double)";
	}

	else{
		m_a=a;
		m_b=b;
		m_M=m;
		m_q=q;
		m_N=(m_b-m_a)*(0.5*m_M*(m_b+m_a)+m_q);
	}
}

void linear::SetParameter(char c, double p){
	switch(c){
		case 'a':
			m_a=p;
			break;
		case 'b':
			m_b=p;
			break;
		case 'm':
			m_M=p;
			break;
		case 'q':
			m_q=p;
			break;
		default:
			cerr << endl << "First argument MUST be chosen between 'a', 'b', 'm' and 'q' for a linear distribution of PDF f(x)=mx+q in the interval [a,b]";
			break;
	}
	m_N=(m_b-m_a)*(0.5*m_M*(m_b+m_a)+m_q);

	if(m_M*m_a+m_q<0. or m_M*m_b+m_q<0.){
		cerr << endl << "PDF is not positively-defined on the given interval, setting all parameters to 0";
		m_a=m_b=m_q=0.;
		m_N=m_M=1.;
	}
}
double linear::GetParameter(char c) const{
	switch(c){
		case 'a':
			return m_a;
		case 'b':
			return m_b;
		case 'm':
			return m_M;
		case 'q':
			return m_q;
		case 'N':
			return m_N;
		default:
			cerr << endl << "Argument MUST be chosen between 'a', 'b', 'm' and 'q' for a linear distribution of PDF f(x)=mx+q in the interval [a,b]" << endl << "write 'N' if you want the normalization constant";
			return -1;
			break;
	}
}
