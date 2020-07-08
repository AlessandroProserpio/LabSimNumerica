#ifndef __funzioniMD_h__
#define __funzioniMD_h__

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Multi_Dim_Function{
	public:
		virtual void SetParameter(char c, double p) =0;
		virtual double GetParameter(char c) const =0;
		virtual double operator()(vector<double> x) const =0;
};

	///////////////// Probability density functions ////////////////////

class HAtom_1s : public Multi_Dim_Function {
	public:
		// lenghts measured in units of Bohr radius
		virtual void SetParameter(char c, double p) {;};
		virtual double GetParameter(char c) const { return 0.; };
		virtual double operator()(vector<double> x) const;
};

class HAtom_2pz : public Multi_Dim_Function {
	public:
		// lenghts measured in units of Bohr radius
		virtual void SetParameter(char c, double p) {;};
		virtual double GetParameter(char c) const { return 0.; };
		virtual double operator()(vector<double> x) const;
};


#endif
