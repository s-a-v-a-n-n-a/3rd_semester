CFLAGS = -g -masm=intel -no-pie -march=native -O3 -std=c++11

link: screen_functions.o radius_vector.o shape.o molecula.o shape_manager.o main.o
	g++ screen_functions.o radius_vector.o shape.o molecula.o shape_manager.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

screen_functions.o: sfml_drawing/screen_functions.cpp
	g++ $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

radius_vector.o: Radius_vector.cpp
	g++ $(CFLAGS) -c -o radius_vector.o Radius_vector.cpp

shape.o: Shape.cpp
	g++ $(CFLAGS) -c -o shape.o Shape.cpp

molecula.o: Molecula.cpp
	g++ $(CFLAGS) -c -o molecula.o Molecula.cpp

shape_manager.o: Shape_manager.cpp
	g++ $(CFLAGS) -c -o shape_manager.o Shape_manager.cpp

clean: 
	rm *.o

run: link
	./main

valgrind: link
	valgrind ./main
