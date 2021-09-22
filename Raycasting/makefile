CFLAGS = -g -masm=intel -no-pie -march=native -O1 -std=c++11

link: main.o screen_functions.o radius_vector.o circle.o lightened_sphere.o colored_point.o
	g++ main.o screen_functions.o radius_vector.o circle.o lightened_sphere.o colored_point.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

screen_functions.o: sfml_drawing/screen_functions.cpp
	g++ $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

# bind_vector.o: shapes/Bind_vector.cpp
# 	g++ $(CFLAGS) -c -o bind_vector.o shapes/Bind_vector.cpp

radius_vector.o: shapes/Radius_vector.cpp
	g++ $(CFLAGS) -c -o radius_vector.o shapes/Radius_vector.cpp

circle.o: shapes/circle.cpp
	g++ $(CFLAGS) -c -o circle.o shapes/circle.cpp

colored_point.o: lighting/Colored_point.cpp
	g++ $(CFLAGS) -c -o colored_point.o lighting/Colored_point.cpp

lightened_sphere.o: shapes/lightened_sphere.cpp
	g++ $(CFLAGS) -c -o lightened_sphere.o shapes/lightened_sphere.cpp

# vector.o: shapes/vector.cpp
# 	g++ $(CFLAGS) -c -o vector.o shapes/vector.cpp

clean: 
	rm *.o

run: link
	valgrind ./main