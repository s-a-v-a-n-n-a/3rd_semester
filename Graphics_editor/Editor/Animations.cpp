#include "Animations.hpp"

Animation::Animation(Animating_texture *par_to_store, Visual_object *par_changable, Full_texture *par_from, Full_texture *par_to, const double par_delta_time)
: changable(par_changable), to_store(par_to_store), texture_from(par_from), texture_to(par_to), delta_time(par_delta_time), current_time(0), alive(true)
{ 
	changable->set_texture(nullptr);
}

Animation::~Animation()
{
	changable->set_texture(to_store);
}

void Animation::tick(const double time)
{
	if (current_time > 1)
	{
		set_alive(false);
		changable->set_texture(to_store);
		((Animating_texture*)(changable->get_texture()))->set_current_texture(texture_to);
		return;
	}

	current_time += delta_time;
}

void Animation::draw(Screen_information *screen)
{
	if (current_time <= 1)
	{
		screen->draw_texture(changable->get_position(), texture_from->get_texture(), changable->get_width(), changable->get_height(), 1 - current_time);
		screen->draw_texture(changable->get_position(), texture_to->get_texture(), changable->get_width(), changable->get_height(), current_time);
	}
}

Animation_manager * Animation_manager::animation_manager = nullptr;
Animation_manager_destroyer Animation_manager::destroyer;

Animation_manager::Animation_manager() : animations() { ; }

Animation_manager * Animation_manager::get_instance() 
{
	if (animation_manager == nullptr)
	{
		animation_manager = new Animation_manager();
		destroyer.initialize(animation_manager);
	}

	return animation_manager;
}

long long Animation_manager::add_animation(Animation *par_animation)
{
	par_animation->set_alive(true);
	animations.add_to_end(par_animation); 

	return animations.get_length() - 1;
}

void Animation_manager::slow_delete_animation(size_t index)
{
	Animation **animations_array = animations.get_array();
	(animations_array[index]->get_changable())->set_texture(animations_array[index]->get_to_store());

	animations.slow_delete(index); 
}

void Animation_manager::tick(const double time)
{
	Animation **animations_array = animations.get_array();
	size_t objects_amount = animations.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (!animations_array[i]->get_alive())
		{
			slow_delete_animation(i);
			i--;
			objects_amount--;
			continue;
		}

		animations_array[i]->tick(time);
	}
}

void Animation_manager::draw(Screen_information *screen)
{
	assert(screen);

	Animation **animations_array = animations.get_array();
	size_t animations_amount = animations.get_length();

	for (size_t i = 0; i < animations_amount; ++i)
	{
		animations_array[i]->draw(screen);
	}
}

Animation_manager_destroyer::~Animation_manager_destroyer() 
{ 
	delete animation_manager; 
}

void Animation_manager_destroyer::initialize(Animation_manager *par_animation_manager) 
{ 
	animation_manager = par_animation_manager; 
}

