LIBS:= Random_generator/random.h cities.h population.h posizione.h

ex09_1.exe: Exercise09_1.o random.o cities.o population.o posizione.o ${LIBS}
	g++ $^ -o ex09_1.exe

Exercise09_1.o: Exercise09_1.cxx ${LIBS}
	g++ -c Exercise09_1.cxx

random.o: Random_generator/random.cpp Random_generator/random.h
	g++ -c Random_generator/random.cpp

cities.o: cities.cxx ${LIBS}
	g++ -c cities.cxx

population.o: population.cxx ${LIBS}
	g++ -c population.cxx

posizione.o: posizione.cxx posizione.h
	g++ -c posizione.cxx

compile:
	make ex09_1.exe

clean: 
	rm *.o

cleanall:
	rm ex09_1.exe

runL1: 
	#rm pop_circle_L1.dat
	#rm pop_square_L1.dat
	./ex09_1.exe
runL2:
	rm pop_circle_L2.dat
	rm pop_square_L2.dat
	./ex09_1.exe
