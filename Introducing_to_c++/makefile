CFLAGS = -g -masm=intel -no-pie -march=native -O1 -std=c++11

link: main.o simple_list.o coordinate_axes.o derived_shapes.o structures.o
	g++ main.o simple_list.o coordinate_axes.o derived_shapes.o structures.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

simple_list.o: simple_list/simple_list.cpp
	g++ $(CFLAGS) -c -o simple_list.o simple_list/simple_list.cpp

coordinate_axes.o: shapes/coordinate_axes.cpp
	g++ $(CFLAGS) -c -o coordinate_axes.o shapes/coordinate_axes.cpp

derived_shapes.o: shapes/derived_shapes.cpp
	g++ $(CFLAGS) -c -o derived_shapes.o shapes/derived_shapes.cpp

structures.o: shapes/structures.cpp
	g++ $(CFLAGS) -c -o structures.o shapes/structures.cpp

clean: 
	rm *.o

run: link
	valgrind ./main