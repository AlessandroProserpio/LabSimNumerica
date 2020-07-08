#include "functions.h"

double max(double a, double b){
	if(a>b)
		return a;
	
	return b;
}

		///////////////////////////////// Test function //////////////////////////////////////////////

PsiT::PsiT(double mu, double sigma){
	m_mu=mu;
	m_sigma=sigma;
}

void PsiT::SetParameter(char c, double x){
	switch(c){
		case 'm':
			m_mu=x;
			break;
		case 's':
			m_sigma=x;
			break;
		default:
			cerr << endl << "First input must be chosen between 'm' or 's' as in: f(x)=exp(-(x \pm m)^2/(2 s^2)))" << endl;
			break;
	}
}

double PsiT::GetParameter(char c) const{
	switch(c){
		case 'm':
			return m_mu;
		case 's':
			return m_sigma;
		default:
			cerr << endl << "Input must be chosen between 'm' or 's' as in: f(x)=exp(-(x \pm m)^2/(2 s^2)))"<< endl;
			return -1;
	}
}


HPsiT::HPsiT(double mu, double sigma){
	m_mu=mu;
	m_sigma=sigma;
}

void HPsiT::SetParameter(char c, double x){
	switch(c){
		case 'm':
			m_mu=x;
			break;
		case 's':
			m_sigma=x;
			break;
		default:
			cerr << endl << "First input must be chosen between 'm' or 's' as in: f(x)=exp(-(x \pm m)^2/(2 s^2)))" << endl;
			break;
	}
}

double HPsiT::GetParameter(char c) const{
	switch(c){
		case 'm':
			return m_mu;
		case 's':
			return m_sigma;
		default:
			cerr << endl << "Input must be chosen between 'm' or 's' as in: f(x)=exp(-(x \pm m)^2/(2 s^2)))"<< endl;
			return -1;
	}
}

double HPsiT::operator()(double x) const{
	double e1=exp(-0.5*pow( (x-m_mu)/m_sigma , 2)), e2=exp(-0.5*pow( (x+m_mu)/m_sigma , 2));
	double V=pow(x, 4)-2.5*x*x;

	return (V+0.5/(m_sigma*m_sigma))*(e1+e2)-0.5*pow( (x-m_mu)/(m_sigma*m_sigma), 2)*e1-0.5*pow( (x+m_mu)/(m_sigma*m_sigma), 2)*e2;
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
