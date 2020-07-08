LIBS:= Random_generator/random.h cities.h population.h posizione.h

ex10_1.exe: Exercise_10_1.o random.o cities.o population.o posizione.o ${LIBS}
	g++ $^ -o ex10_1.exe

ex10_2.exe: Exercise_10_2.o random.o cities.o population.o posizione.o ${LIBS}
	mpicxx $^ -o ex10_2.exe

Exercise_10_2.o: Exercise_10_2.cxx ${LIBS}
	mpicxx -c Exercise_10_2.cxx

Exercise_10_1.o: Exercise_10_1.cxx ${LIBS}
	g++ -c Exercise_10_1.cxx

random.o: Random_generator/random.cpp Random_generator/random.h
	g++ -c Random_generator/random.cpp

cities.o: cities.cxx ${LIBS}
	g++ -c cities.cxx

population.o: population.cxx ${LIBS}
	g++ -c population.cxx

posizione.o: posizione.cxx posizione.h
	g++ -c posizione.cxx

compile:
	make ex10_1.exe
	make ex10_2.exe

clean: 
	rm *.o

cleanall:
	rm ex10_1.exe
	rm ex10_2.exe

run10.1:
	rm path_length_circle.dat
	rm path_length_square.dat
	./ex10_1.exe

run10.2:
	mpiexec -np 4 ./ex10_2.exe
