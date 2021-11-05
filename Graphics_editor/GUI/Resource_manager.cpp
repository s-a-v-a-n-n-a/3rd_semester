#include "Resources_manager.hpp"

Resources * Resources::Resources = nullptr;
Resources_destroyer Resources::destroyer;

Resources::Resources() : textures() { ; 
Resources::~Resources()
{
	long long textures_amount = (long long)textures.get_length();

	for (long long i = textures_amount; i >= 0; --i)
	{
		textures.delete_from_end();
	}
}

Full_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height)
{
	Full_texture *new_texture = new Full_texture(texture_name, texture_width, texture_height);

	textures.add_to_end(new_texture);

	return new_texture;
}

Animating_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height, const char *move_texture_name, const char *inactive_texture_name)
{
	Animating_texture *new_texture = new Animating_texture(texture_name, texture_width, texture_height);
	if (move_texture_name)
		new_texture->set_move_texture(move_texture_name);
	if (inactive_texture_name)
		new_texture->set_inactive_texture(inactive_texture_name);
	
	textures.add_to_end(new_texture);

	return new_texture;
}

Resources * Resources::get_instance() 
{
	if (Resources == nullptr)
	{
		Resources = new Resources();
		destroyer.initialize(Resources);
	}

	return Resources;
}

Resources_destroyer::~Resources_destroyer() 
{ 
	delete Resources; 
}

void Resources_destroyer::initialize(Resources *par_animation_manager) 
{ 
	animation_manager = par_animation_manager; 
}
