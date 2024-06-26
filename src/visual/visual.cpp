#ifndef __openwars__game__visual__visual__cpp__
#define __openwars__game__visual__visual__cpp__

#include "visual.hpp"
#include <new>

namespace Raylib {
	#include <raylib.h>
};

namespace OpenWars {
	typedef struct {
		bool				is_bitmap;
		Raylib::Texture2D	*tex;
	} c_texture_thingy_t;

	// "pixels" as Big-Endian RGBA8888, from top-left to bottom-right.
	ErrorOr<texture_t *> create_bitmap_texture(u16 width, u16 height, u8 *pixels) {
		texture_t *tex;
		c_texture_thingy_t *thing;

		try {
			tex = new texture_t;
			thing = new c_texture_thingy_t;
		} catch(std::bad_alloc &e) {
			return Error {
				"Couldn't allocate enough memory for a bitmap texture"
			};
		};

		Raylib::Image r_img = Raylib::GenImageColor(width, height, Raylib::BLACK);

		Raylib::Color *r_col = Raylib::LoadImageColors(r_img);

		u64 iwh = (width * height * 4);

		for(u64 i = 0; i < iwh; i += 4) {
			r_col[i] = {
				pixels[i | 0x0],
				pixels[i | 0x1],
				pixels[i | 0x2],
				pixels[i | 0x3],
			};
		};

		Raylib::Texture2D r_tex = Raylib::LoadTextureFromImage(r_img);
		Raylib::UnloadImage(r_img);

		tex->width = width;
		tex->height = height;
		thing->is_bitmap = true;
		thing->tex = (&r_tex);

		tex->data_ptr = (uintptr_t)thing;

		return tex;
	};

	ErrorOr<void> draw_texture(texture_t *texture, float x, float y, float w, float h, float a, float t) {
		(void)t;

		if(texture == nullptr)
			return Error { "Texture pointer is NULL" };

		if(texture->data_ptr == 0)
			return Error { "Texture data pointer is NULL" };

		c_texture_thingy_t *thing = (c_texture_thingy_t *)texture->data_ptr;

		if(thing->is_bitmap) {
			Raylib::DrawTexturePro(
				*thing->tex,
				{
					0, 0,
					(float)thing->tex->width,
					(float)thing->tex->height,
				},
				{
					x, y,
					w, h,
				},
				{ 0.0, 0.0 },
				a,
				Raylib::WHITE
			);

			return Error { nullptr };
		} else {
			return Error { "Vector textures are TODOs" };
		}
	};

	void free_texture(texture_t *texture) {
		if(texture == nullptr)
			return;
		if(texture->data_ptr == 0)
			return;

		c_texture_thingy_t *thing = (c_texture_thingy_t *)texture->data_ptr;

		if(thing->is_bitmap) {
			if(thing->tex != nullptr) {
				Raylib::UnloadTexture(*thing->tex);
				thing->tex = nullptr;
			}

			delete thing;
			thing = nullptr;
		} else {
			// [TODO] Handle vector stuff.
			return;
		}

		delete texture;
		texture = nullptr;
	};
};

#endif
