CFLAGS = -g -masm=intel -no-pie -march=native -O3 -std=c++11

link: screen_functions.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o tools_vidget.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o main.o
	g++ screen_functions.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o tools_vidget.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

# graphic shell
# -----------------------------------------------------------------------------------
screen_functions.o: sfml_drawing/screen_functions.cpp
	g++ $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

texture_names.o: sfml_drawing/Texture_names.cpp
	g++ $(CFLAGS) -c -o texture_names.o sfml_drawing/Texture_names.cpp

sfml_text.o: sfml_drawing/Text.cpp
	g++ $(CFLAGS) -c -o sfml_text.o sfml_drawing/Text.cpp
# -----------------------------------------------------------------------------------


# math
# -----------------------------------------------------------------------------------
# Vector_ll.o: math_structures/Vector_ll.cpp
# 	g++ $(CFLAGS) -c -o Vector_ll.o math_structures/Vector_ll.cpp
# -----------------------------------------------------------------------------------


# visual objects
# -----------------------------------------------------------------------------------
visual_base.o: GUI/Visual_object_base.cpp
	g++ $(CFLAGS) -c -o visual_base.o GUI/Visual_object_base.cpp

button.o: GUI/Button.cpp
	g++ $(CFLAGS) -c -o button.o GUI/Button.cpp

button_manager.o: GUI/Button_manager.cpp
	g++ $(CFLAGS) -c -o button_manager.o GUI/Button_manager.cpp

resource_manager.o: GUI/Resource_manager.cpp
	g++ $(CFLAGS) -c -o resource_manager.o GUI/Resource_manager.cpp

animations.o: GUI/Animations.cpp
	g++ $(CFLAGS) -c -o animations.o GUI/Animations.cpp
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

graphical_delegate.o: Editor/Graphical_delegates.cpp
	g++ $(CFLAGS) -c -o graphical_delegate.o Editor/Graphical_delegates.cpp

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
