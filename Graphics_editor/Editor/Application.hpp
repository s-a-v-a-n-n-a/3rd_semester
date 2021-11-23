#ifndef APPLICATION_H
#define APPLICATION_H

#include "../sfml_drawing/screen_functions.hpp"
#include "../GUI/Visual_object_base.hpp"

#include "Graphical_editor_main_page.hpp"

extern const size_t DEFAULT_SIZE;

class Application;

class Application_destroyer
{
private:
	Application *app;

public:
	~Application_destroyer();

	void initialize(Application *par_application);
};

class Application
{
private:
	static Application *app;
	static Application_destroyer destroyer;
	
	Screen_information *graphics_wrapper;

	Visual_object *current_main;
	Visual_object *default_main;

protected:
	Application();
	friend class Application_destroyer;

public:
	~Application();
	static Application *get_app();

	void set_default();
	void set_main(Visual_object *object);

	void draw();
	void tick();

	void launch();
};

#endif // APPLICATION_H
