LIBS:= Random_generator/random.h blocking_method.h functions.h

ex08_1.exe: exercise08_1.o random.o blocking_method.o functions.o ${LIBS}
	g++ $^ -o ex08_1.exe

exercise08_1.o: exercise08_1.cxx ${LIBS}
	g++ -c exercise08_1.cxx

random.o: Random_generator/random.cpp ${LIBS}
	g++ -c Random_generator/random.cpp

functions.o: functions.cxx functions.h 
	g++ -c functions.cxx

blocking_method.o: ../libs/blocking_method.cxx ../libs/blocking_method.h
	g++ -c ../libs/blocking_method.cxx

compile:
	make ex08_1.exe

clean: 
	rm *.o

cleanall:
	rm ex08_1.exe

run: 
	./ex08_1.exe
