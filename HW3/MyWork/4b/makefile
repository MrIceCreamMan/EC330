# define the GCC variable
GCC = g++ 

b: main_b.o
	${GCC} main_b.o -o b

a: main_a.o LinkedList.o
	${GCC} main_a.o LinkedList.o -o a

main_a.o: main_a.cpp
	${GCC} -c main_a.cpp

main_b.o: main_b.cpp
	${GCC} -c main_b.cpp

LinkedList.o: LinkedList.cpp
	${GCC} -c LinkedList.cpp

clean:
	rm *.o b
