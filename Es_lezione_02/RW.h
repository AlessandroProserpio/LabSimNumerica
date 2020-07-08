#ifndef __RW_h__
#define __RW_h__

#include "posizione.h"
#include "../Random_generator/random.h"

class Random_Walk3D{
	Posizione m_x;			// position of the walker
	unsigned int m_nsteps;		// # of steps
	double m_a;			// average distance per step
	double * m_distance;		// saves distance from starting point in each step
	Random gen;

	public:	
	// constructors
	Random_Walk3D(unsigned int nsteps, double a);
	Random_Walk3D(Posizione x0, unsigned int nsteps, double a);
	Random_Walk3D(double x0, double y0, double z0, unsigned int nsteps, double a);
	// destructor
	~Random_Walk3D();

	// methods to access private members
	void Set_Nsteps(unsigned int nsteps);
	void Set_Start(Posizione x0) { m_x=x0; };
	void Set_Start(double x0, double y0, double z0) { m_x.SetXYZ(x0, y0, z0); };
	void Set_to_zero();
	void Set_x_to_zero() {	m_x.SetXYZ(0., 0., 0.); };
	void Set_distance_to_zero();
	double * Get_distance() const { return m_distance; };
	Posizione Get_x() const { return m_x; };

	// 3d random walks
	void Cubic_Lattice();
	void Isotropic_Space();
};

#endif
