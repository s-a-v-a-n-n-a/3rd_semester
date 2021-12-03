#include <cstdio>
#include <cstdlib>

#include <crand>

#include "Editor/Application.hpp"

int main()
{
	std::srand(std::time(0));
	 
	Application::get_app()->launch();
}