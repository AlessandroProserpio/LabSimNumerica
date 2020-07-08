#include "population.h"


item::item(const Cities c):
	m_probPP(pPP),
	m_probS(pS),
	m_probP(pP),
	m_probI(pI)
{
	m_size=c.GetNcities();

	for(int i=0; i<m_size; i++)
		m_person.push_back(i+1);

	Calculate_L1(c);
	Calculate_L2(c);
}

item::item(item i0, int i, int j, const Cities c):
	m_probPP(pPP),
	m_probS(pS),
	m_probP(pP),
	m_probI(pI)
{
	m_size=i0.GetSize();
	vector<int> newperson;

	for(int k=0; k<m_size; k++)
		newperson.push_back(i0[k]);
	
	swap(newperson[i], newperson[j]);

	m_person=newperson;

	Calculate_L1(c);
	Calculate_L2(c);
}

item::item(item i0, const Cities c):
	m_probPP(pPP),
	m_probS(pS),
	m_probP(pP),
	m_probI(pI)
{
	m_size=i0.GetSize();
	vector<int> newperson;

	for(int k=0; k<m_size; k++)
		newperson.push_back(i0[k]);

	m_person=newperson;

	Calculate_L1(c);
	Calculate_L2(c);
}

item::item(vector<int> pos, const Cities c):
	m_probPP(pPP),
	m_probS(pS),
	m_probP(pP),
	m_probI(pI)
{
	m_size=pos.size();
	for(int i=0; i<m_size; i++)
		m_person.push_back(pos[i]);

	Calculate_L1(c);
	Calculate_L2(c);
}

int item::Next(int i) const{
	if(i==m_size-1)
		return 1;

	return 1+i;
}

void item::Calculate_L1(const Cities c){
	m_L1=0.;

	for(int i=0; i<c.GetNcities(); i++)
		m_L1+=c.Calculate_distance(m_person[i]-1, m_person[Next(i)]-1);
}

void item::Calculate_L2(const Cities c){
	m_L2=0.;

	for(int i=0; i<c.GetNcities(); i++)
		m_L2+=pow(c.Calculate_distance(m_person[i]-1, m_person[Next(i)]-1) , 2);
}

// Mutations
void item::Mutate(const Cities c, Random& m_gen){
	
	if(m_gen.Rannyu()<m_probPP)
		GM_Pair_Permutation(c, m_gen);
	if(m_gen.Rannyu()<m_probS)
		GM_Shift(c, m_gen);
	if(m_gen.Rannyu()<m_probP)
		GM_Block_Permutation(c, m_gen);
	if(m_gen.Rannyu()<m_probI)
		GM_Inversion(c, m_gen);
}

void item::GM_Pair_Permutation(const Cities c, Random& m_gen){
	int i=m_gen.Discrete_Unif(1, m_size-1, 1), j=m_gen.Discrete_Unif(1, m_size-1, 1);
	swap(m_person[i], m_person[j]);
	Calculate_L1(c);
	Calculate_L2(c);
}
void item::GM_Shift(const Cities c, Random& m_gen){
	int i=m_gen.Discrete_Unif(1, m_size-2, 1);					// starting point of the block
	int m=m_gen.Discrete_Unif(1, m_size-1-i, 1);					// length of the block
	int n=m_gen.Discrete_Unif(1, m_size-1-i-m, 1);					// magnitude of the shift
	rotate(m_person.begin()+i, m_person.begin()+i+m, m_person.begin()+i+m+n-1);

	Calculate_L1(c);
	Calculate_L2(c);
}
void item::GM_Block_Permutation(const Cities c, Random& m_gen){
	int i=m_gen.Discrete_Unif(1, m_size-1, 1), j=m_gen.Discrete_Unif(1, m_size-1, 1);	// starting points
	int m=m_gen.Discrete_Unif(1, m_size-1-max(i,j), 1);					// length

	for(int k=0; k<m; k++)
		swap(m_person[i+k], m_person[j+k]);

	Calculate_L1(c);
	Calculate_L2(c);
}

void item::GM_Inversion(const Cities c, Random& m_gen){
	int i=m_gen.Discrete_Unif(1, m_size-1, 1);
	int m=m_gen.Discrete_Unif(1, m_size-i, 1);

	int mid=m/2;
	for(int k=0; k<mid; k++)
		swap(m_person[i+k], m_person[i+k+mid]);

	Calculate_L1(c);
	Calculate_L2(c);
}

	// Crossover
vector<int> item::Crossover(int cut, vector<int> consort, const Cities c){
	vector<int> ip;

	for(int i=0; i<m_size; i++){
		if(!count(m_person.begin(), m_person.begin()+cut, i+1))
			ip.push_back( distance(consort.begin() , find(consort.begin(), consort.end(), i+1)));
	}

	sort(ip.begin(), ip.end());

	vector<int> oldp=m_person;
	
	for(int i=0; i<ip.size(); i++)
		m_person.pop_back();

	for(int i=0; i<ip.size(); i++)
		m_person.push_back(consort[ip[i]]);

	Calculate_L1(c);
	Calculate_L2(c);

	return oldp;
}

// Print
void item::PrintPath(ofstream& fout){
	int wd=5;
	for(int i=0; i<m_size; i++)
		fout << m_person[i] << setw(wd);
}

void item::PrintPath(){
	int wd=5;
	for(int i=0; i<m_size; i++)
		cout << m_person[i] << setw(wd);
}

item& item::operator=(const item& i0){
	m_size=i0.GetSize();
	m_person.clear();
	for(int i=0; i<m_size; i++)
		m_person.push_back(i0[i]);
	m_L1=i0.GetL1();
	m_L2=i0.GetL2();
	return *this;
}

// SIMULATED ANNEALING
void item::Simulated_Annealing(const Cities c, Random& gen){

	for(int i=0; i<m_nsteps; i++){
		item nuovo=*this;
		int a=gen.Discrete_Unif(0, 3, 1);

		if(a==0) 
			nuovo.GM_Pair_Permutation(c, gen);
		else if(a==1)
			nuovo.GM_Shift(c, gen);
		else if(a==2)
			nuovo.GM_Block_Permutation(c, gen);
		else if(a==3)
			nuovo.GM_Inversion(c, gen);

		double A=exp( -m_beta*(nuovo.GetL1()-m_L1) );
		//double A=exp( -m_beta(nuovo.GetL2()-m_L2) );

		if(A>gen.Rannyu())
			*this=nuovo;
	}
}

////////////////////////// SORTCRYTERIA ///////////////////////////

bool sortcryteria::sort_by_L1(item a, item b){ return a.GetL1() < b.GetL1(); }

bool sortcryteria::sort_by_L2(item a, item b){ return a.GetL2() < b.GetL2(); }
