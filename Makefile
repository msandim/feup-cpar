all: prog_cpp prog_java

prog_cpp:
	g++ prog_cpp.cpp -o prog_cpp.o -l papi -fopenmp -O3
	
prog_java:
	javac prog_java.java

clean:
	\rm *.o *.class *.out

test:
	make all
	./prog_cpp.o
	java prog_java	
	
test_file:
	make all
	#alinea 1
	./prog_cpp.o 0 0 600 3000 400 > output.out
	java prog_java 0 600 3000 400 >> output.out
	
	#alinea 2
	./prog_cpp.o 1 0 600 3000 400 >> output.out
	./prog_cpp.o 1 0 4000 10000 2000 >> output.out
	java prog_java 1 600 3000 400 >> output.out
	java prog_java 1 4000 10000 2000 >> output.out
	
	#alinea 3
	./prog_cpp.o 0 1 600 3000 400 >> output.out
	./prog_cpp.o 0 2 600 3000 400 >> output.out
	./prog_cpp.o 0 3 600 3000 400 >> output.out
	./prog_cpp.o 0 4 600 3000 400 >> output.out
	./prog_cpp.o 1 1 600 3000 400 >> output.out
	./prog_cpp.o 1 2 600 3000 400 >> output.out
	./prog_cpp.o 1 3 600 3000 400 >> output.out
	./prog_cpp.o 1 4 600 3000 400 >> output.out
