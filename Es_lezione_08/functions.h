#ifndef __funzioni_h__
#define __funzioni_h__

#include <iostream>
#include <cmath>

using namespace std;

double max(double a, double b);

class function{
	public:
		virtual void SetParameter(char c, double p) =0;
		virtual double GetParameter(char c) const =0;
		virtual double operator()(double x) const =0;
};

	//////////////////////////////// Test function /////////////////////////////////

class PsiT : public function{
	double m_mu, m_sigma;

	public:
	// constructor
	PsiT(double mu, double sigma);
	// methods to access private members
	void SetParameter(char c, double p);
	double GetParameter(char c) const;
	// virtual methods
	virtual double operator()(double x) const { return exp(-0.5*pow( (x-m_mu)/m_sigma , 2))+exp(-0.5*pow( (x+m_mu)/m_sigma , 2)); };
};

class HPsiT : public function{
	double m_mu, m_sigma;

	public:
	// constructor
	HPsiT(double mu, double sigma);
	// methods to access private members
	void SetParameter(char c, double p);
	double GetParameter(char c) const;
	// virtual methods
	virtual double operator()(double x) const;
};

	////////////////////////// Probability Density Functions /////////////////////

class uniform_1d : public function{
	double m_a, m_b;

	public:
	// constructor
	uniform_1d(double a, double b) { m_a=-max(-a, -b); m_b=max(a, b); };
	// methods to access private members
	virtual void SetParameter(char c, double p);
	virtual double GetParameter(char c) const;
	// evaluate
	virtual double operator()(double x) const { return 1./(m_b-m_a); };

};

class gauss : public function{
	double m_mu, m_sigma;

	public:
	// constructor
	gauss(double mu, double sigma) { m_mu=mu; m_sigma=sigma; };
	// methods to access private members
	virtual void SetParameter(char c, double p);
	virtual double GetParameter(char c) const;
	// evaluate
	virtual double operator()(double x) const { return 1./(sqrt(2*M_PI)*m_sigma)*exp(-0.5*pow((x-m_mu)/m_sigma, 2)); };
};

class exp_distr : public function{
	double m_lambda;

	public:
	// constructor
	exp_distr(double lambda) { m_lambda=lambda; };
	// methods to access private members
	virtual void SetParameter(char c, double p);
	virtual double GetParameter(char c) const;
	// evaluate
	virtual double operator()(double x) const { return m_lambda*exp(-m_lambda*x); };
};

class cauchy_lorentz : public function{
	double m_mu, m_Gamma;

	public:
	// constructor
	cauchy_lorentz(double mu, double Gamma) { m_mu=mu; m_Gamma=Gamma; };
	// methods to access private members
	virtual void SetParameter(char c, double p);
	virtual double GetParameter(char c) const;
	// evaluate
	virtual double operator()(double x) const { return m_Gamma/M_PI*1./(pow(x-m_mu, 2)+m_Gamma*m_Gamma); };
};

class linear : public function{
	double m_M, m_q, m_N;
	double m_a, m_b;

	public:
	// constructor
	linear(double a, double b, double m, double q);
	// methods to access private members
	virtual void SetParameter(char c, double p);
	virtual double GetParameter(char c) const;
	// evaluate
	virtual double operator()(double x) const { return (m_M*x+m_q)/m_N; };
};

#endif
