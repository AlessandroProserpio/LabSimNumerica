LIBS:= Random_generator/random.h blocking_method.h multidimfunctions.h posizione.h

ex05_1.exe: exercise05_1.o random.o blocking_method.o multidimfunctions.o posizione.o ${LIBS}
	g++ $^ -o ex05_1.exe

exercise05_1.o: exercise05_1.cxx ${LIBS}
	g++ -c exercise05_1.cxx

random.o: Random_generator/random.cpp ${LIBS}
	g++ -c Random_generator/random.cpp

multidimfunctions.o: multidimfunctions.cxx multidimfunctions.h 
	g++ -c multidimfunctions.cxx

posizione.o: posizione.cxx posizione.h
	g++ -c posizione.cxx

blocking_method.o: blocking_method.cxx blocking_method.h
	g++ -c blocking_method.cxx

compile:
	make ex05_1.exe

clean: 
	rm *.o

cleanall:
	rm ex05_1.exe

run: 
	rm 1s-orbital.dat
	rm 2pz-orbital.dat
	./ex05_1.exe
