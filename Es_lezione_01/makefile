LIBS:= Random_generator/random.h blocking_method.h

ex01_1.exe: exercise01_1.o random.o blocking_method.o ${LIBS}
	g++ $^ -o ex01_1.exe

ex01_2.exe: exercise01_2.o random.o 
	g++ $^ -o ex01_2.exe

ex01_3.exe: exercise01_3.o random.o blocking_method.o ${LIBS}
	g++ $^ -o ex01_3.exe

exercise01_1.o: exercise01_1.cxx ${LIBS}
	g++ -c exercise01_1.cxx

exercise01_2.o: exercise01_2.cxx ../Random_generator/random.h
	g++ -c exercise01_2.cxx

exercise01_3.o: exercise01_3.cxx ${LIBS}
	g++ -c exercise01_3.cxx

random.o: Random_generator/random.cpp
	g++ -c Random_generator/random.cpp

blocking_method.o: blocking_method.cxx blocking_method.h
	g++ -c blocking_method.cxx

compile:
	make ex01_1.exe
	make ex01_2.exe
	make ex01_3.exe

clean: 
	rm *.o

cleanall:
	rm ex01_1.exe
	rm ex01_2.exe
	rm ex01_3.exe

run: 
	./ex01_1.exe
	./ex01_2.exe
	./ex01_3.exe
