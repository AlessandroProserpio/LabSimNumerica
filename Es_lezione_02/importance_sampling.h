#ifndef __impsamp_h__
#define __impsamp_h__

#include <iostream>
#include "functions.h"
#include "../Random_generator/random.h"
#include "../libs/blocking_method.h"

using namespace std;

class Importance_Sampling{
	const function * m_f;
	double m_sum;
	unsigned int m_niter, m_nblocks, m_L;
	double * m_ave, * m_aveprog, * m_err;

	protected:
	Random gen;
	double m_a, m_b;
	function * m_p; 
	virtual double Generate() { return -1; }; 	// not set to zero just to make the Run() method work, should not be used in this form

	public:
	// constructors
	Importance_Sampling();

	// methods to access private members
	void Set_distrib_params(char c, double p) { m_p->SetParameter(c, p); }; 
	unsigned int Get_Nsteps() const { return m_niter; };
	unsigned int Get_Nblocks() const { return m_nblocks; };
	double Get_Estimate() const;
	double Get_Error() const;
	double * Get_Estimate_Prog() const { return m_aveprog; };
	double * Get_Error_Prog() const { return m_err; };

	// evaluating integrals
	void Run(const function* f, unsigned int nsteps, unsigned int nblocks);
};

class IS_Uniform : public Importance_Sampling{
	protected:
	double Generate() { return gen.Rannyu(m_p->GetParameter('a'), m_p->GetParameter('b')); };
	public:
	// constructor
	IS_Uniform(double a, double b);
};

class IS_Gauss : public Importance_Sampling{
	protected:
	double Generate() { return gen.Gauss(m_p->GetParameter('m'), m_p->GetParameter('s')); };
	public:
	// constructor
	IS_Gauss(double mu, double sigma);
};

class IS_Cauchy_Lorentz : public Importance_Sampling{
	protected:
	double Generate() { return gen.Cauchy(m_p->GetParameter('G'), m_p->GetParameter('m')); };
	public:
	// constructor
	IS_Cauchy_Lorentz(double mu, double Gamma);
};

class IS_Exp : public Importance_Sampling{
	protected:
	double Generate() { return gen.Exp(m_p->GetParameter('l')); };
	public:
	// constructor
	IS_Exp(double lambda);
};

class IS_Linear : public Importance_Sampling{
	protected:
	double Generate();
	public:
	// constructor
	IS_Linear(double a, double b, double m, double q);
};

#endif
