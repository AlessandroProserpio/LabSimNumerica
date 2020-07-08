#include "importance_sampling.h"

	// constructors
Importance_Sampling::Importance_Sampling(){
	m_a=m_b=m_sum=0.;
	m_niter=m_nblocks=m_L=0;
	m_f=m_p=NULL;
	m_ave=m_aveprog=m_err=NULL;
	// inizializza generatore di numeri casuali se necessario
}

	// methods to access private members
double Importance_Sampling::Get_Estimate() const{
	if(m_aveprog==NULL){
		cerr << endl << "No evaluation has been made";
		return -1;
	}

	return m_aveprog[m_nblocks-1];
}

double Importance_Sampling::Get_Error() const{
	if(m_err==NULL){
		cerr << endl << "No evaluation has been made";
		return -1;
	}

	return m_err[m_nblocks-1];
}

	// integral estimator
void Importance_Sampling::Run(const function* f, unsigned int niter, unsigned int nblocks){
	m_niter=niter;
	m_nblocks=nblocks;
	m_L=m_niter/m_nblocks;
	m_ave=new double[m_nblocks];
	m_aveprog=new double[m_nblocks];
	m_err=new double[m_nblocks];
	double ave2[m_nblocks];
	m_f=f;
	
	m_sum=0.;

	for(unsigned int i=0; i<m_niter; i++){
		double x=Generate();
		m_sum+=(*m_f)(x)/(*m_p)(x);
		check(m_L, i+1, m_ave, ave2, &m_sum);
	}

	Blocking_Method(m_nblocks, m_ave, ave2, m_aveprog, m_err);
}

	// derived classes constructors
IS_Uniform::IS_Uniform(double a, double b){
	m_p=new uniform_1d(a, b);
	m_a=m_p->GetParameter('a');
	m_b=m_p->GetParameter('b');
}

IS_Gauss::IS_Gauss(double mu, double sigma){
	m_p=new gauss(mu, sigma);
}

IS_Cauchy_Lorentz::IS_Cauchy_Lorentz(double mu, double Gamma){
	m_p=new cauchy_lorentz(mu, Gamma);
}

IS_Exp::IS_Exp(double lambda){
	m_p=new exp_distr(lambda);
}

IS_Linear::IS_Linear(double a, double b, double m, double q){
	m_p=new linear(a, b, m, q);
	m_a=m_p->GetParameter('a');
	m_b=m_p->GetParameter('b');
}

double IS_Linear::Generate(){
	double m=m_p->GetParameter('m'), q=m_p->GetParameter('q'), N=m_p->GetParameter('N');
	double Delta=pow(q/m+m_a, 2)+2*m*N*gen.Rannyu();
	double x1=-q/m+sqrt(Delta);
	double x2=-q/m-sqrt(Delta);

	if(x1<m_b)
		return x1;

	return x2;
}
