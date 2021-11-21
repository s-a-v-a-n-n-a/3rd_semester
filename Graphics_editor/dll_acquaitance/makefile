all:
	g++ -fPIC -shared dynamic_library.cpp -o dynamic.so
	g++ main.cpp -ldl -o main

clean: 
	rm *.o

run: all
	./main