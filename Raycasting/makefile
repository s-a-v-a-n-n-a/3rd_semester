CFLAGS = -g -masm=intel -no-pie -march=native -O1 -std=c++11

link: main.o screen_functions.o circle.o lightened_sphere.o vector.o
	g++ main.o screen_functions.o circle.o lightened_sphere.o vector.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

screen_functions.o: sfml_drawing/screen_functions.cpp
	g++ $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

circle.o: shapes/circle.cpp
	g++ $(CFLAGS) -c -o circle.o shapes/circle.cpp

lightened_sphere.o: shapes/lightened_sphere.cpp
	g++ $(CFLAGS) -c -o lightened_sphere.o shapes/lightened_sphere.cpp

vector.o: shapes/vector.cpp
	g++ $(CFLAGS) -c -o vector.o shapes/vector.cpp

clean: 
	rm *.o

run: link
	valgrind ./main