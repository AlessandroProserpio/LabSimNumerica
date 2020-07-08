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

#define pPP 0.07
#define pS 0.07
#define pP 0.08
#define pI 0.07
#define pc 0.8
#define q 1.65

using namespace std;


class item{
	vector<int> m_person;
	int m_size;
	double m_L1, m_L2;
	double m_probPP, m_probS, m_probP, m_probI;

	protected:
	int Next(int i) const;

	public:
	// constructor(s)
	item() {;};
	item(const Cities c);
	item(item i0, int i, int j, const Cities c);
	item(item i0, const Cities c);
	item(vector<int> pos, const Cities c);
	// Access to private members
	int GetSize() const { return m_size; };
	int operator[](int i) const { return m_person[i]; };
	vector<int> GetPerson() const { return m_person; };
	double GetL1() const { return m_L1; };
	double GetL2() const { return m_L2; };
	// calculate lengths
	void Calculate_L1(const Cities c);
	void Calculate_L2(const Cities c);
	// print
	void PrintPath(ofstream& fout);
	void PrintPath();
	// mutations
	void GM_Pair_Permutation(const Cities c, Random& m_gen);
	void GM_Shift(const Cities c, Random& m_gen);
	void GM_Block_Permutation(const Cities c, Random& m_gen);
	void GM_Inversion(const Cities c, Random& m_gen);

	// GENETICAL ALGORITHM 
	void Mutate(const Cities c, Random& m_gen);				// runs all mutations at once w/ probability
	vector<int> Crossover(int cut, vector<int> consort, const Cities c); 	// returns old m_person

	// SIMULATED ANNEALING
	private:
	double m_beta;
	int m_nsteps;
	public:
	void Set_Params(double beta, int nsteps) { m_beta=beta; m_nsteps=nsteps; };
	void Simulated_Annealing(const Cities c, Random& gen);

	item& operator=(const item& i0);

};

namespace sortcryteria{
	bool sort_by_L1(item a, item b);
	bool sort_by_L2(item a, item b);
}

#endif
