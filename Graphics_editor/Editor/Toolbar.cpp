#include "Toolbar.hpp"

Toolbar *Toolbar::toolbar = nullptr;
Toolbar_destroyer Toolbar::destroyer;

Toolbar::Toolbar()
: tools(), active_tool(nullptr) 
{
	Pencil *pencil = new Pencil();
	add_tool(pencil);

	Eraser *eraser = new Eraser();
	add_tool(eraser);

	tools_amount = tools.get_length();
	set_active_tool(pencil);
}

Toolbar *Toolbar::get_instance()
{
	if (toolbar == nullptr)
	{
		toolbar = new Toolbar();
		destroyer.initialize(toolbar);
	}

	return toolbar;
}

void Toolbar::add_tool(Tool *tool)
{
	tools.add_to_end(tool);
}

void Toolbar::set_active_tool(Tool *tool)
{
	active_tool = tool;
}

Tool *Toolbar::get_active_tool()
{
	return active_tool;
}

List<Tool*> *Toolbar::get_tools()
{
	return &tools;	
}

void Toolbar::set_color(const Color &color)
{
	current_color = color;

	active_tool->set_color(color);
}

Color Toolbar::get_color() const
{
	return current_color;
}

size_t Toolbar::get_tools_amount() const
{
	return tools_amount;
}



Toolbar_destroyer::~Toolbar_destroyer() 
{ 
	delete toolbar; 
}

void Toolbar_destroyer::initialize(Toolbar *par_toolbar) 
{ 
	toolbar = par_toolbar; 
}
