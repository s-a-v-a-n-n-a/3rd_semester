#ifndef ANIMATING_TEXTURE_H
#define ANIMATING_TEXTURE_H

#include "../sfml_drawing/screen_functions.hpp"
#include "../sfml_drawing/Texture.hpp"

class Animating_texture : public Full_texture
{
private:
	Full_texture *inactive_texture;
	Full_texture *default_texture;
	Full_texture *move_texture;

public:
	Animating_texture(const char *par_texture_name, const size_t width, const size_t height)
	: Full_texture(par_texture_name, width, height), default_texture(nullptr), move_texture(nullptr), inactive_texture(nullptr) 
	{ 
		default_texture = new Full_texture(par_texture_name, width, height);

		// current_texture = default_texture; 
		move_texture = nullptr;
		inactive_texture = nullptr;
	}
	~Animating_texture()
	{
		if (inactive_texture)
			delete inactive_texture;

		if (move_texture)
			delete move_texture;

		if (default_texture)
			delete default_texture;
	}

	void set_move_texture(const char *par_texture)
	{
		move_texture = new Full_texture(par_texture, get_size().get_x(), get_size().get_y());
	}

	void set_inactive_texture(const char *par_texture)
	{
		inactive_texture = new Full_texture(par_texture, get_size().get_x(), get_size().get_y());
	}

	void set_current_texture(Full_texture *par_texture)
	{
		set_texture(par_texture->get_texture());
	}

	Full_texture *get_inactive_texture() { return inactive_texture; }
	Full_texture *get_default_texture() { return default_texture; }
	Full_texture *get_move_texture() { return move_texture; }
};

#endif // ANIMATING_TEXTURE_H
