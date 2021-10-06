CFLAGS = -g -masm=intel -no-pie -march=native -O0 -std=c++11

link: screen_functions.o radius_vector.o shape.o molecula.o rectangle.o accelerating_rectangle.o shape_manager.o collisions_detections.o collisions_reactions.o visual_base.o visual_manager.o amounts_graph.o button.o main.o
	g++ screen_functions.o radius_vector.o shape.o molecula.o rectangle.o accelerating_rectangle.o shape_manager.o collisions_detections.o collisions_reactions.o visual_base.o visual_manager.o amounts_graph.o button.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

# graphic shell
# -----------------------------------------------------------------------------------
screen_functions.o: sfml_drawing/screen_functions.cpp
	g++ $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp
# -----------------------------------------------------------------------------------


# math
# -----------------------------------------------------------------------------------
radius_vector.o: math_structures/Radius_vector.cpp
	g++ $(CFLAGS) -c -o radius_vector.o math_structures/Radius_vector.cpp
# -----------------------------------------------------------------------------------


# shapes themselves
# -----------------------------------------------------------------------------------
shape.o: Shape_base/Shape.cpp
	g++ $(CFLAGS) -c -o shape.o Shape_base/Shape.cpp

molecula.o: Shapes/Molecula.cpp
	g++ $(CFLAGS) -c -o molecula.o Shapes/Molecula.cpp

rectangle.o: Shapes/Rectangle.cpp
	g++ $(CFLAGS) -c -o rectangle.o Shapes/Rectangle.cpp

accelerating_rectangle.o: Shapes/Accelerating_rectangle.cpp
	g++ $(CFLAGS) -c -o accelerating_rectangle.o Shapes/Accelerating_rectangle.cpp
# -----------------------------------------------------------------------------------


# visual objects
# -----------------------------------------------------------------------------------
visual_base.o: GUI/Visual_object_base.cpp
	g++ $(CFLAGS) -c -o visual_base.o GUI/Visual_object_base.cpp

visual_manager.o: GUI/Visual_objects_manager.cpp
	g++ $(CFLAGS) -c -o visual_manager.o GUI/Visual_objects_manager.cpp

button.o: GUI/Button.cpp
	g++ $(CFLAGS) -c -o button.o GUI/Button.cpp

amounts_graph.o: GUI/Amounts_graph.cpp
	g++ $(CFLAGS) -c -o amounts_graph.o GUI/Amounts_graph.cpp

shape_manager.o: Shape_manager/Shape_manager.cpp
	g++ $(CFLAGS) -c -o shape_manager.o Shape_manager/Shape_manager.cpp
# -----------------------------------------------------------------------------------


# chemistry
# -----------------------------------------------------------------------------------
collisions_detections.o: Shapes_interactions/Collisions_detections.cpp
	g++ $(CFLAGS) -c -o collisions_detections.o Shapes_interactions/Collisions_detections.cpp

collisions_reactions.o: Shapes_interactions/Collisions_reactions.cpp
	g++ $(CFLAGS) -c -o collisions_reactions.o Shapes_interactions/Collisions_reactions.cpp
# -----------------------------------------------------------------------------------

clean: 
	rm *.o

run: link
	./main

valgrind: link
	valgrind --leak-check=full ./main
