all: prog_cpp prog_java

prog_cpp:
	g++ prog_cpp.cpp -o prog_cpp.o -l papi -fopenmp -O3
	
prog_java:
	javac prog_java.java

clean:
	\rm *.o *.class *.csv

test:
	make all
	./prog_cpp.o 0 0 3 3 400 1
	./prog_cpp.o 0 1 3 3 400 1
	./prog_cpp.o 1 0 3 3 400 1
	./prog_cpp.o 1 1 3 3 400 1
	java prog_java 0 3 3 400 1
	java prog_java 1 3 3 400 1
	
csv:
	make all
	#alinea 1
	./prog_cpp.o 0 0 600 3000 400 0 > output.csv
	java prog_java 0 600 3000 400 0 >> output.csv
	
	#alinea 2
	./prog_cpp.o 1 0 600 3000 400 0 >> output.csv
	java prog_java 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 0 4000 10000 2000 0 >> output.csv
	
	#alinea 3
	./prog_cpp.o 0 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 2 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 3 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 4 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 2 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 3 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 4 600 3000 400 0 >> output.csv
