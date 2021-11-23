COMPILATOR = g++
CFLAGS = -g -masm=intel -no-pie -march=native -O3 -std=c++17

link: screen_functions.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o color_picker.o gradient_bar.o color_selection.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o interpolation.o spline.o slider.o toolbar.o app.o main.o
	$(COMPILATOR) screen_functions.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o palette.o canvas_mm.o tab.o editor_delegate.o color_picker.o gradient_bar.o color_selection.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o interpolation.o spline.o slider.o toolbar.o app.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	$(COMPILATOR) $(CFLAGS) -c -o main.o main.cpp

# graphic shell
# -----------------------------------------------------------------------------------
screen_functions.o: sfml_drawing/screen_functions.cpp
	$(COMPILATOR) $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

texture_names.o: sfml_drawing/Texture_names.cpp
	$(COMPILATOR) $(CFLAGS) -c -o texture_names.o sfml_drawing/Texture_names.cpp

sfml_text.o: sfml_drawing/Text.cpp
	$(COMPILATOR) $(CFLAGS) -c -o sfml_text.o sfml_drawing/Text.cpp
# -----------------------------------------------------------------------------------


# math
# -----------------------------------------------------------------------------------
# Vector_ll.o: math_structures/Vector_ll.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o Vector_ll.o math_structures/Vector_ll.cpp
interpolation.o: math_structures/Interpolator.cpp
	$(COMPILATOR) $(CFLAGS) -c -o interpolation.o math_structures/Interpolator.cpp
# -----------------------------------------------------------------------------------


# visual objects
# -----------------------------------------------------------------------------------
visual_base.o: GUI/Visual_object_base.cpp
	$(COMPILATOR) $(CFLAGS) -c -o visual_base.o GUI/Visual_object_base.cpp

button.o: GUI/Button.cpp
	$(COMPILATOR) $(CFLAGS) -c -o button.o GUI/Button.cpp

button_manager.o: GUI/Button_manager.cpp
	$(COMPILATOR) $(CFLAGS) -c -o button_manager.o GUI/Button_manager.cpp

spline.o: GUI/Spline.cpp
	$(COMPILATOR) $(CFLAGS) -c -o spline.o GUI/Spline.cpp

slider.o: GUI/Slider.cpp
	$(COMPILATOR) $(CFLAGS) -c -o slider.o GUI/Slider.cpp

resource_manager.o: GUI/Resource_manager.cpp
	$(COMPILATOR) $(CFLAGS) -c -o resource_manager.o GUI/Resource_manager.cpp

animations.o: GUI/Animations.cpp
	$(COMPILATOR) $(CFLAGS) -c -o animations.o GUI/Animations.cpp
# -----------------------------------------------------------------------------------


# editor part
# -----------------------------------------------------------------------------------
# Editor/%.o: Editor/%.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o canvas Editor/Canvas.cpp
app.o: Editor/Application.cpp
	$(COMPILATOR) $(CFLAGS) -c -o app.o Editor/Application.cpp

toolbar.o: Editor/Toolbar.cpp 
	$(COMPILATOR) $(CFLAGS) -c -o toolbar.o Editor/Toolbar.cpp

canvas.o: Editor/Canvas.cpp
	$(COMPILATOR) $(CFLAGS) -c -o canvas.o Editor/Canvas.cpp

palette.o: Editor/Palette.cpp
	$(COMPILATOR) $(CFLAGS) -c -o palette.o Editor/Palette.cpp

tab.o: Editor/Tab.cpp
	$(COMPILATOR) $(CFLAGS) -c -o tab.o Editor/Tab.cpp

editor_delegate.o: Editor/Editor_delegates.cpp
	$(COMPILATOR) $(CFLAGS) -c -o editor_delegate.o Editor/Editor_delegates.cpp

graphical_delegate.o: Editor/Graphical_delegates.cpp
	$(COMPILATOR) $(CFLAGS) -c -o graphical_delegate.o Editor/Graphical_delegates.cpp

gradient_bar.o: Editor/Gradient_bar.cpp
	$(COMPILATOR) $(CFLAGS) -c -o gradient_bar.o Editor/Gradient_bar.cpp

color_picker.o: Editor/Color_picker.cpp
	$(COMPILATOR) $(CFLAGS) -c -o color_picker.o Editor/Color_picker.cpp

color_selection.o: Editor/Color_selection.cpp
	$(COMPILATOR) $(CFLAGS) -c -o color_selection.o Editor/Color_selection.cpp

canvas_manager.o: Editor/Canvas_manager.cpp
	$(COMPILATOR) $(CFLAGS) -c -o canvas_manager.o Editor/Canvas_manager.cpp

canvas_mm.o: Editor/Canvas_manager_manager.cpp
	$(COMPILATOR) $(CFLAGS) -c -o canvas_mm.o Editor/Canvas_manager_manager.cpp

window_control_panel.o: Editor/Window_control_panel.cpp
	$(COMPILATOR) $(CFLAGS) -c -o window_control_panel.o Editor/Window_control_panel.cpp

graphical_editor.o: Editor/Graphical_editor_main_page.cpp
	$(COMPILATOR) $(CFLAGS) -c -o graphical_editor.o Editor/Graphical_editor_main_page.cpp
# -----------------------------------------------------------------------------------

clean: 
	rm *.o

run: link
	./main

valgrind: link
	valgrind --leak-check=full ./main
