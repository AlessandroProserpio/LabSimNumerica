#ifndef __population_h__
#define __population_h__


#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Random_generator/random.h"
#include "cities.h"

#define pPP 0.05
#define pS 0.05
#define pP 0.08
#define pI 0.05
#define pc 0.7
#define q 1.6

using namespace std;


class item{
	vector<int> m_person;
	int m_size;
	double m_L1, m_L2;
	double m_probPP, m_probS, m_probP, m_probI;

	protected:
	int Next(int i) const;

	public:
	// constructor
	item(const Cities c);
	item(item i0, int i, int j, const Cities c);
	item(item i0, const Cities c);
	// Access to private members
	int GetSize() const { return m_size; };
	int operator[](int i) const { return m_person[i]; };
	vector<int> GetPerson() const { return m_person; };
	double GetL1() const { return m_L1; };
	double GetL2() const { return m_L2; };
	// calculate lengths
	void Calculate_L1(const Cities c);
	void Calculate_L2(const Cities c);
	// mutations
	void Mutate(const Cities c, Random& m_gen);					// runs all mutations at once
	void GM_Pair_Permutation(const Cities c, Random& m_gen);
	void GM_Shift(const Cities c, Random& m_gen);
	void GM_Block_Permutation(const Cities c, Random& m_gen);
	void GM_Inversion(const Cities c, Random& m_gen);	
	// crossover
	vector<int> Crossover(int cut, vector<int> consort, const Cities c); 		// returns old m_person
	// print
	void PrintPath(ofstream& fout);

};

class Population{
	int m_size;
	double m_probC;
	vector<item> m_pop;
	Random m_gen;
	Cities* m_c;

	protected:
	// rigged selector
	int Select();

	public:
	// constructors
	Population(int npop, Cities c);
	// sort
	void SortL1();
	void SortL2();
	// new generation creator
	void New_generation();
	// print
	void PrintPath(ofstream& fout, int cut);
	void PrintL1(ofstream& fout, int cut);
	void PrintL2(ofstream& fout, int cut);
};

namespace sortcryteria{
	bool sort_by_L1(item a, item b);
	bool sort_by_L2(item a, item b);
}

#endif
