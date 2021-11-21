#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Pencil.hpp"

class Toolbar;

class Toolbar_destroyer
{
private:
	Toolbar *toolbar;

public:
	~Toolbar_destroyer();

	void initialize(Toolbar *par_toolbar);
};

class Toolbar
{
private:
	static Toolbar *toolbar;
	static Toolbar_destroyer destroyer;

	List<Tool*> tools;

	Tool *active_tool;

protected:
// public:
	Toolbar();
	friend class Toolbar_destroyer;

public:
	static Toolbar *get_instance();

	void add_tool(Tool *tool);

	void set_active_tool(Tool *tool);
	
	Tool *get_active_tool();
	List<Tool*> *get_tools();
};

#endif // TOOLBAR_H
