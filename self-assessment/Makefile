# Makefile

self.exe: self-assessment.o
	g++ self-assessment.o -o self.exe

self-assessment.o: self-assessment.cpp
	g++ -c -o self-assessment.o self-assessment.cpp

clean:
	rm *.o *.exe