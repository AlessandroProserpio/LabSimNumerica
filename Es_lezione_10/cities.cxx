#include "cities.h"


Cities::Cities(){
	m_positions=NULL;
	m_ncities=0;
}

Cities::Cities(string filename, int Ncities){
	m_ncities=Ncities;
	m_positions=new Posizione[m_ncities];
	ifstream fin;
	fin.open(filename);

	for(int i=0; i<m_ncities; i++){
		double x, y, z;
		fin >> x >> y >> z;
		m_positions[i].SetXYZ(x, y, z);
	}
	fin.close();	
}
void Cities::Cities_in_circle(int ncities, double r){
	m_ncities=ncities;

	if(m_positions==NULL)
		delete [] m_positions;

	m_positions=new Posizione[m_ncities];
	//m_positions[0].SetXYZ(r, 0., 0.);
	
	for(int i=0; i<m_ncities; i++){
		double phi=m_gen.Rannyu(0., 2.*M_PI);
		m_positions[i].SetXYZ(r*cos(phi), r*sin(phi), 0.);
	}
		
}

void Cities::Cities_in_square(int ncities, double side){
	m_ncities=ncities;

	if(m_positions==NULL)
		delete [] m_positions;

	m_positions=new Posizione[m_ncities];
	m_positions[0].SetXYZ(m_gen.Rannyu(0., side), m_gen.Rannyu(0., side), 0.);

	for(unsigned int i=1; i<m_ncities; i++){
		double x=m_gen.Rannyu(0., side), y=m_gen.Rannyu(0., side);
		// kind of useless for so few cities
		/*for(int j=0; j<i; j++){
			if(x==m_positions[i].GetX() and y==m_positions[i].GetY()){
				x=gen.Rannyu(0., side);
				y=gen.Rannyu(0., side);
				j=0;
			}
		}*/
		m_positions[i].SetXYZ(x, y, 0.);
	}
}

void Cities::Print(ofstream& fout) const{
	int wd=20;
	for(int i=0; i<m_ncities; i++)
		fout << m_positions[i].GetX() << setw(wd) << m_positions[i].GetY() << setw(wd) << m_positions[i].GetZ() << endl;
}

void Cities::Print() const{
	int wd=20;
	for(int i=0; i<m_ncities; i++)
		cout << m_positions[i].GetX() << setw(wd) << m_positions[i].GetY() << setw(wd) << m_positions[i].GetZ() << endl;
}
