#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdio>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "../math_structures/Radius_vector.hpp"
#include "../simple_list/simple_list.hpp"
#include "colors.hpp"

#define Shelled_texture sf::Texture // sf::RenderTexture

class Texture
{
private:
	char *texture_name;
	Vector_ll size;

public:
	Texture(const char *par_texture_name) : texture_name(nullptr), size(0, 0)
	{
		unsigned texture_length = strlen(par_texture_name) + 1;

		texture_name = new char[texture_length];
		memset(texture_name, 0, texture_length);
		strncpy(texture_name, par_texture_name, texture_length - 1);

		sf::Texture texture;
		texture.loadFromFile(par_texture_name);
		sf::Vector2u sfml_size = texture.getSize();

		size = Vector_ll(sfml_size.x, sfml_size.y);
	}

	~Texture()
	{
		delete [] texture_name;
	}

	long long get_width() const { return size.get_x(); }
	long long get_height() const { return size.get_y(); }

	virtual void set_size(const Vector_ll par_size) 
	{ 
		size = par_size;
	}

	char *get_name() { return texture_name; }
	virtual Shelled_texture *get_texture() { return NULL; }
	virtual void set_texture(Color *array, const size_t width, const size_t height) { ; }
};

class Full_texture : public Texture
{
private:
	// const Shelled_texture *texture;
	Shelled_texture texture;

public:
	Full_texture(const char *par_texture_name) : Texture(par_texture_name)
	{
		texture.loadFromFile(par_texture_name);
	}

	virtual void set_size(const Vector_ll par_size) 
	{ 
		Texture::set_size(par_size);

		// texture.setSize(sf::Vector2u(get_width(), get_height()));
	}

	~Full_texture() = default;

	Shelled_texture *get_texture() override { return &texture; }
	void set_texture(Color *array, const size_t width, const size_t height) override { texture.update((sf::Uint8*)array, width, height, 0, 0); }
};

class Texture_manager
{
private: 
	// List<Texture*> textures_definitions;
	List<Full_texture*> textures;

public:
	Texture_manager() : textures() { ; }
	~Texture_manager() = default;

	Shelled_texture *add_texture(const char *texture_name)
	{
		Full_texture *texture = new Full_texture(texture_name);
		textures.add_to_end(texture);

		return texture->get_texture();
	}

	Shelled_texture *get_texture(const char *texture_name)
	{
		Full_texture **textures_array = textures.get_array();
		size_t textures_amount = textures.get_length();

		for (size_t i = 0; i < textures_amount; ++i)
		{
			if (!strcmp(textures_array[i]->get_name(), texture_name))
				return textures_array[i]->get_texture();
		}

		return add_texture(texture_name);
	}
};

#endif // TEXTURE_H
