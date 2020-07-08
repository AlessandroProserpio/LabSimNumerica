#include "cities.h"
#include "population.h"
#include <string>

int main(){
	
	const int ncities=32;
	const int npop=300;
	const int ngen=2000;
	//const int iprint=ngen;

	Cities c;

		// Cities in circle
	c.Cities_in_circle(ncities, 1.);
	Population pop1(npop, c);
	pop1.SortL1();
	//pop1.sortL2();

	ofstream Pop;

	cout << endl << "---------------- Cities in a circle -----------------";
		

	for(int j=0; j<ngen; j++){
		pop1.New_generation();
		pop1.SortL1();
		//pop1.SortL2();
		if((j+1)%100==0)
			cout << endl << "Generation #" << j+1;
		//Pop.open("pop_circle_L2.dat", ios::app);
		Pop.open("pop_circle_L1.dat", ios::app);
		pop1.PrintL1(Pop, npop/2);
		Pop << endl;
		Pop.close();	
	}		
	cout << endl;

	// Print
	ofstream Circle;
	Circle.open("cities_in_circle.dat");
	c.Print(Circle);
	Circle.close();

	Pop.open("pop_circle_best_path.dat");
	pop1.PrintPath(Pop, 1);
	Pop << endl;
	pop1.PrintL1(Pop, 1);
	Pop.close();


		// Cities in square
	c.Cities_in_square(ncities, 1.);
	Population pop2(npop, c);
	pop2.SortL1();
	//pop2.SortL2();

	cout << endl << "---------------- Cities in a square ------------------";

	for(int j=0; j<ngen; j++){
		pop2.New_generation();
		pop2.SortL1();
		//pop2.SortL2();
		if((j+1)%100==0)
			cout << endl << "Generation #" << j+1;
		//if((j+1)%iprint==0){
			//Pop.open("pop_circle_L2.dat", ios::app);
			Pop.open("pop_square_L1.dat", ios::app);
			pop2.PrintL1(Pop, npop/2);
			Pop << endl;
			Pop.close();	
		//}
	}		
	cout << endl;

	// print
	ofstream Square;
	Square.open("cities_in_square.dat");
	c.Print(Square);
	Square.close();

	Pop.open("pop_square_best_path.dat");
	pop2.PrintPath(Pop, 1);
	Pop << endl;
	pop2.PrintL1(Pop, 1);
	Pop.close();

return 0;
}
