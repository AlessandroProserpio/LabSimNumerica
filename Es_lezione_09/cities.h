#ifndef __cities_h__
#define __cities_h__

#include "Random_generator/random.h"
#include "posizione.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

class Cities {
	protected:
	Random m_gen;
	int m_ncities;
	Posizione* m_positions;

	public:
	// constructor(s)
	Cities();
	// methods to place cities
	void Cities_in_circle(int ncities, double r);		// cities on a circle of given radius
	void Cities_in_square(int ncities, double side);	// cities in a square of given side
	// methods
	double Calculate_distance(int i, int j) const { return (m_positions[i]-m_positions[j]).GetR(); };
	int GetNcities() const { return m_ncities; };
	void Print(ofstream& fout) const;
};

#endif
