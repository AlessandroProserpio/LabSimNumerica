LIBS1:= functions.h importance_sampling.h Random_generator/random.h blocking_method.h
LIBS2:= Random_generator/random.h posizione.h RW.h blocking_method.h

ex02_1.exe: exercise02_1.o random.o blocking_method.o functions.o importance_sampling.o ${LIBS1}
	g++ $^ -o ex02_1.exe

ex02_2.exe: exercise02_2.o random.o posizione.o blocking_method.o RW.o ${LIBS2}
	g++ $^ -o ex02_2.exe

exercise02_1.o: exercise02_1.cxx ${LIBS1}
	g++ -c exercise02_1.cxx

exercise02_2.o: exercise02_2.cxx ${LIBS2}
	g++ -c exercise02_2.cxx

random.o: Random_generator/random.cpp Random_generator/random.h
	g++ -c Random_generator/random.cpp

functions.o: functions.cxx functions.h	
	g++ -c functions.cxx

importance_sampling.o: importance_sampling.cxx ${LIBS1}
	g++ -c importance_sampling.cxx

posizione.o: posizione.cxx posizione.h
	g++ -c posizione.cxx

RW.o: RW.h RW.cxx ${LIBS2}
	g++ -c RW.cxx

blocking_method.o: blocking_method.cxx blocking_method.h
	g++ -c blocking_method.cxx

compile:
	make ex02_1.exe
	make ex02_2.exe

clean: 
	rm *.o

cleanall:
	rm ex02_1.exe
	rm ex02_2.exe

run: 
	./ex02_1.exe
	./ex02_2.exe

