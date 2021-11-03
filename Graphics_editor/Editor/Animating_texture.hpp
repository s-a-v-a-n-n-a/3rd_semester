#ifndef ANIMATING_TEXTURE_H
#define ANIMATING_TEXTURE_H

#include "../sfml_drawing/screen_functions.hpp"
#include "../sfml_drawing/Texture.hpp"

class Animating_texture : public Full_texture
{
private:
	Full_texture *current_texture;
	// sf::RenderTexture render_texture;

	Full_texture *inactive_texture;
	Full_texture *default_texture;
	Full_texture *move_texture;

public:
	Animating_texture(const char *par_texture_name)
	: Full_texture(par_texture_name), default_texture(nullptr), move_texture(nullptr), inactive_texture(nullptr) 
	{ 
		default_texture = new Full_texture(par_texture_name);

		current_texture = default_texture; 
		move_texture = nullptr;
		inactive_texture = nullptr;

		// texture = &render_texture.getTexture();
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

	void set_current_texture(Full_texture *par_texture) { current_texture = par_texture; }

	void set_move_texture(const char *par_texture)
	{
		move_texture = new Full_texture(par_texture);
	}

	void set_inactive_texture(const char *par_texture)
	{
		inactive_texture = new Full_texture(par_texture);
	}

	Full_texture *get_inactive_texture() { return inactive_texture; }
	Full_texture *get_default_texture() { return default_texture; }
	Full_texture *get_move_texture() { return move_texture; }

	Shelled_texture *get_texture() override { return current_texture->get_texture(); }
};

#endif // ANIMATING_TEXTURE_H
