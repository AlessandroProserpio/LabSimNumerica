LIBS:= Random_generator/random.h functions.h blocking_method.h

ex03_1.exe: exercise03_1.o random.o functions.o blocking_method.o ${LIBS}
	g++ $^ -o ex03_1.exe

exercise03_1.o: exercise03_1.cxx ${LIBS}
	g++ -c exercise03_1.cxx

random.o: Random_generator/random.cpp Random_generator/random.h
	g++ -c Random_generator/random.cpp

functions.o: functions.cxx functions.h	
	g++ -c .functions.cxx

blocking_method.o: blocking_method.cxx blocking_method.h
	g++ -c blocking_method.cxx

compile:
	make ex03_1.exe

clean: 
	rm *.o

cleanall:
	rm ex03_1.exe

run: 
	./ex03_1.exe
