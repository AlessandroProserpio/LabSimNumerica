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
	GM_Pair_Permutation(c, m_gen);
		//cout << endl << "Mutazione 1" << endl;
	GM_Shift(c, m_gen);
		//cout <<  "Mutazione 2" << endl;
	GM_Block_Permutation(c, m_gen);
		//cout <<  "Mutazione 3" << endl;
	GM_Inversion(c, m_gen);
		//cout <<  "Mutazione 4" << endl;
}

void item::GM_Pair_Permutation(const Cities c, Random& m_gen){

	if(m_gen.Rannyu()>m_probPP)
		return;

	int i=m_gen.Discrete_Unif(1, m_size-1, 1), j=m_gen.Discrete_Unif(1, m_size-1, 1);
	swap(m_person[i], m_person[j]);
	Calculate_L1(c);
	Calculate_L2(c);
}
void item::GM_Shift(const Cities c, Random& m_gen){

	if(m_gen.Rannyu()>m_probS)
		return;

	//cout << endl << "Shift eseguito" << endl;
	int i=m_gen.Discrete_Unif(1, m_size-2, 1);					// starting point of the block
		//cout << i << endl;
	int m=m_gen.Discrete_Unif(1, m_size-1-i, 1);					// length of the block
		//cout << m_size-1-i << endl;
	int n=m_gen.Discrete_Unif(1, m_size-1-i-m, 1);					// magnitude of the shift
		//cout << m_size-1-i-m << endl;
	rotate(m_person.begin()+i, m_person.begin()+i+m, m_person.begin()+i+m+n-1);

	Calculate_L1(c);
	Calculate_L2(c);
}
void item::GM_Block_Permutation(const Cities c, Random& m_gen){
	
	if(m_gen.Rannyu()>m_probP)
		return;

	int i=m_gen.Discrete_Unif(1, m_size-1, 1), j=m_gen.Discrete_Unif(1, m_size-1, 1);	// starting points
	int m=m_gen.Discrete_Unif(1, m_size-1-max(i,j), 1);					// length

	for(int k=0; k<m; k++)
		swap(m_person[i+k], m_person[j+k]);

	Calculate_L1(c);
	Calculate_L2(c);
}

void item::GM_Inversion(const Cities c, Random& m_gen){
	
	if(m_gen.Rannyu()>m_probI)
		return;

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


			///////////////////////////////// POPULATION /////////////////////////////////////
Population::Population(int size, Cities c):
	m_probC(pc)
{
	m_size=size;
	m_c=&c;
	item i0(*m_c);
	m_pop.push_back(i0);

	for(int i=1; i<m_size; i++){
		int k=m_gen.Discrete_Unif(1, m_c->GetNcities()-1, 1), m=m_gen.Discrete_Unif(1, m_c->GetNcities()-1, 1);
		item I(m_pop[i-1], k, m, *m_c);
		m_pop.push_back(I);
	}

}

int Population::Select(){
	int j=int(m_size*pow(m_gen.Rannyu(), q));	
	
	return j;	
}
void Population::SortL1(){
	sort(m_pop.begin(), m_pop.end(), sortcryteria::sort_by_L1);
}

void Population::SortL2(){
	sort(m_pop.begin(), m_pop.end(), sortcryteria::sort_by_L2);
}

void Population::New_generation(){
	vector<item> newpop;

	do{
		int i_father=Select(), i_mother;
		item father(m_pop[i_father], *m_c);
		do{
			i_mother=Select();
		}while(i_mother==i_father);
		item mother(m_pop[i_mother], *m_c);

		father.Mutate(*m_c, m_gen);
		mother.Mutate(*m_c, m_gen);
		//cout << endl << "Mutazioni eseguite" << endl;

		if(m_gen.Rannyu() < m_probC){
			int cut=m_gen.Discrete_Unif(1, father.GetSize()-1, 1);
			vector<int> appo=father.Crossover(cut, mother.GetPerson(), *m_c);
			mother.Crossover(cut, appo, *m_c);
		}
		//cout << endl << "Crossover eseguito" << endl;
		newpop.push_back(father);
		newpop.push_back(mother);
	}while(newpop.size() < m_pop.size() );

	//cout << endl << "Generazione completata" << endl;

	if(newpop.size() > m_pop.size())
		newpop.pop_back();
	
	m_pop=newpop;	
}

void Population::PrintPath(ofstream& fout, int cut){
	for(int i=0; i<cut; i++){
		m_pop[i].PrintPath(fout);
		fout << endl;
	}
}

void Population::PrintL1(ofstream& fout, int cut){
	for(int i=0; i<cut; i++)
		fout << m_pop[i].GetL1() << endl;
}

void Population::PrintL2(ofstream& fout, int cut){
	for(int i=0; i<cut; i++)
		fout << m_pop[i].GetL2() << endl;
}
		////////////////////////// SORTCRYTERIA ///////////////////////////

bool sortcryteria::sort_by_L1(item a, item b){
	return a.GetL1() < b.GetL1();
}

bool sortcryteria::sort_by_L2(item a, item b){
	return a.GetL2() < b.GetL2();
}
