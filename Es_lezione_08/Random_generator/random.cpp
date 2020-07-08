/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

Random :: Random(){
	int seed[4];
	int p1, p2;
	ifstream Primes("../Random_generator/Primes");
 	if (Primes.is_open()){
 		Primes >> p1 >> p2 ;
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("../Random_generator/seed.in");
	string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				SetRandom(seed,p1,p2);
			}
		}
	input.close();
	} 
	else cerr << "PROBLEM: Unable to open seed.in" << endl;
}

Random :: ~Random(){}

void Random :: SaveSeed(){
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Gauss(double mean, double sigma) {
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

double Random :: Rannyu(double min, double max){
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

double Random :: Exp(double lambda){
	return -log(1-Rannyu())/lambda;
}

double Random :: Cauchy(double gamma, double mu){
	return mu+gamma*tan(M_PI*(Rannyu()-0.5));
}

void Random :: SetRandom(int * s, int p1, int p2){
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0]%4096;
  l2 = s[1]%4096;
  l3 = s[2]%4096;
  l4 = s[3]%4096;
  l4 = 2*(l4/2)+1;
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}

int Random::Discrete_Unif(int min, int max, unsigned int step){
	unsigned int k=0;
	double ran=Rannyu();
	int h=(max-min)/step+1;		// # of progressive integers in the interval [min, max] at mutual distance = step
	while(ran>(k+1.)/h)
		k+=step;

	return k+min;

}

double Random::Metropolis_Step(function* f, char opt, double x0, double delta, unsigned int* count){
	double xnew, x;
	switch(opt){
		case 'U':
			x=Rannyu(x0-0.5*delta, x0+0.5*delta);
		break;
		case 'G':
			x=Gauss(x0, delta);
		break;
	}
	if(A(f, x, x0) > Rannyu()){
		(*count)++;
		xnew=x;
	}
	else
		xnew=x0;

	return xnew;
}

double Random::A(function* f, double x2, double x1){
	
	double f2=(*f)(x2), f1=(*f)(x1);
	double A=pow( f2/f1, 2);

	if(A<1.)
		return A;
	
	return 1.;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
