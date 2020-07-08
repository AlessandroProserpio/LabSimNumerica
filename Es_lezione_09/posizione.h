#ifndef __posizione_h__
#define __posizione_h__

#include<iostream>
#include <cmath>

using namespace std;

class Posizione{
	
	double m_1, m_2, m_3;

	public:
	// constructors;
	Posizione();
	Posizione(double, double, double);

	//  const methods:
	double GetX() const {return m_1;};
	double GetY() const {return m_2;};
	double GetZ() const {return m_3;};
	double GetR() const {return sqrt(pow(m_1,2)+pow(m_2,2)+pow(m_3,2));};
	double GetRho() const {return sqrt(pow(m_1,2)+pow(m_2,2));};		
	double GetPhi() const {return atan2(m_2,m_1);};
	double GetTheta() const {return acos(m_3/GetR());};	
	
	double Distance(const Posizione& p ) const {return sqrt(pow(GetX()-p.GetX(),2)+pow(GetY()-p.GetY(),2)+pow(GetZ()-p.GetZ(),2));};

	// methods to modify private members
	void SetComponent(unsigned int i, double val);
	void SetXYZ(double, double, double);
	void Set_to_zero();
	
	// algebra
	Posizione& operator=(const Posizione &);
	Posizione operator+(const Posizione&);
	Posizione operator-(const Posizione&);
	Posizione& operator+=(const Posizione&);
};

#endif
