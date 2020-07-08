#include "RW.h"

	// constructors
Random_Walk3D::Random_Walk3D(unsigned int nsteps, double a){
	m_x.Set_to_zero();
	m_nsteps=nsteps;
	m_a=a;
	m_distance=new double[m_nsteps];
}

Random_Walk3D::Random_Walk3D(Posizione x0, unsigned int nsteps, double a){
	m_x=x0;
	m_nsteps=nsteps;
	m_a=a;
	m_distance=new double[m_nsteps];
}

Random_Walk3D::Random_Walk3D(double x0, double y0, double z0, unsigned int nsteps, double a){
	m_x.SetXYZ(x0, y0, z0);
	m_nsteps=nsteps;
	m_a=a;
	m_distance=new double[m_nsteps];
}

	// destructors
Random_Walk3D::~Random_Walk3D(){
	delete [] m_distance;
}

	// methods to access private members
void Random_Walk3D::Set_Nsteps(unsigned int nsteps){
	m_nsteps=nsteps;
	delete [] m_distance;
	m_distance=new double[m_nsteps];
}

void Random_Walk3D::Set_to_zero(){
	m_x.SetXYZ(0., 0., 0.);

	for(unsigned int i=0; i<m_nsteps; i++)
		m_distance[i]=0.;
}

void Random_Walk3D::Set_distance_to_zero(){
	for(unsigned int i=0; i<m_nsteps; i++)
		m_distance[i]=0.;
}

	// 3d random walks
void Random_Walk3D::Cubic_Lattice(){
	Posizione x0=m_x;
	for(unsigned int i=0; i<m_nsteps; i++){
		unsigned int j=gen.Discrete_Unif(0, 2, 1);	// j "chooses" the direction of the the walker in each step, provided each of the three is equally probable
		int k=gen.Discrete_Unif(-1, 1, 2);		// the walker is equally likely to move back or forth
		Posizione y;
		y.SetComponent(j, m_a*k);
		m_x+=y;

		m_distance[i]=pow(m_x.Distance(x0), 2);
	}
}

void Random_Walk3D::Isotropic_Space(){
	Posizione x0=m_x;
	for(unsigned int i=0; i<m_nsteps; i++){
		double theta=gen.Rannyu(0., M_PI);
		double phi=gen.Rannyu(0., 2*M_PI);

		Posizione y(m_a*sin(theta)*cos(phi), m_a*sin(theta)*sin(phi), m_a*cos(theta));
		m_x+=y;

		m_distance[i]=pow(m_x.Distance(x0), 2);
	}
}
