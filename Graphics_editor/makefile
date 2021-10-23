CFLAGS = -g -masm=intel -no-pie -march=native -O2 -std=c++11

link: screen_functions.o radius_vector.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o tools_vidget.o button_manager.o main.o
	g++ screen_functions.o radius_vector.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o tools_vidget.o button_manager.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

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


# visual objects
# -----------------------------------------------------------------------------------
visual_base.o: GUI/Visual_object_base.cpp
	g++ $(CFLAGS) -c -o visual_base.o GUI/Visual_object_base.cpp

button.o: GUI/Button.cpp
	g++ $(CFLAGS) -c -o button.o GUI/Button.cpp

button_manager.o: GUI/Button_manager.cpp
	g++ $(CFLAGS) -c -o button_manager.o  GUI/Button_manager.cpp
# -----------------------------------------------------------------------------------


# editor part
# -----------------------------------------------------------------------------------
# Editor/%.o: Editor/%.cpp
# 	g++ $(CFLAGS) -c -o canvas Editor/Canvas.cpp

canvas.o: Editor/Canvas.cpp
	g++ $(CFLAGS) -c -o canvas.o Editor/Canvas.cpp

palette.o: Editor/Palette.cpp
	g++ $(CFLAGS) -c -o palette.o Editor/Palette.cpp

tab.o: Editor/Tab.cpp
	g++ $(CFLAGS) -c -o tab.o Editor/Tab.cpp

editor_delegate.o: Editor/Editor_delegates.cpp
	g++ $(CFLAGS) -c -o editor_delegate.o Editor/Editor_delegates.cpp

tools_vidget.o: Editor/Tools_vidget.cpp
	g++ $(CFLAGS) -c -o tools_vidget.o Editor/Tools_vidget.cpp

canvas_manager.o: Editor/Canvas_manager.cpp
	g++ $(CFLAGS) -c -o canvas_manager.o Editor/Canvas_manager.cpp

canvas_mm.o: Editor/Canvas_manager_manager.cpp
	g++ $(CFLAGS) -c -o canvas_mm.o Editor/Canvas_manager_manager.cpp

window_control_panel.o: Editor/Window_control_panel.cpp
	g++ $(CFLAGS) -c -o window_control_panel.o Editor/Window_control_panel.cpp

graphical_editor.o: Editor/Graphical_editor_main_page.cpp
	g++ $(CFLAGS) -c -o graphical_editor.o Editor/Graphical_editor_main_page.cpp
# -----------------------------------------------------------------------------------

clean: 
	rm *.o

run: link
	./main

valgrind: link
	valgrind --leak-check=full ./main
