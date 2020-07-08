#include "posizione.h"

Posizione::Posizione(){
	m_1=0.;
	m_2=0.;
	m_3=0.;
}

Posizione::Posizione(double x, double y, double z){
	m_1=x;
	m_2=y;
	m_3=z;
}

void Posizione::SetComponent(unsigned int i, double val){
	switch(i){
		case 0:
			m_1=val;	
			break;
		case 1:
			m_2=val;
			break;
		case 2:
			m_2=val;
			break;
		default:
			cout << endl << "i must range from 0 to 2";
			break;
	}

}

void Posizione::SetXYZ(double x, double y, double z){
	m_1=x;
	m_2=y;
	m_3=z;
}

void Posizione::Set_to_zero(){
	m_1=0.;
	m_2=0.;
	m_3=0.;
}

Posizione& Posizione::operator=(const Posizione & p){
	SetXYZ(p.GetX(),p.GetY(),p.GetZ());
	return *this;
}

Posizione Posizione::operator+(const Posizione & q){
	Posizione newpos(GetX()+q.GetX(),GetY()+q.GetY(),GetZ()+q.GetZ());
	return newpos;
}

Posizione Posizione::operator-(const Posizione & q){
	Posizione newpos(GetX()-q.GetX(),GetY()-q.GetY(),GetZ()-q.GetZ());
	return newpos;
}

Posizione& Posizione::operator+=(const Posizione& p){
	SetXYZ(GetX()+p.GetX(), GetY()+p.GetY(), GetZ()+p.GetZ());
	return *this;
}
