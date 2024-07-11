#ifndef __openwars__game__visual__visual__hpp__
#define __openwars__game__visual__visual__hpp__

#include "../defs.hpp"

namespace OpenWars {
	typedef struct _color_t {
		u8	r = 0xff;
		u8	g = 0x00;
		u8	b = 0xff;
		u8	a = 0xff;
	} color_t;

	typedef struct {
		u32				width;
		u32				height;
		uintptr_t		data_ptr;
	} texture_t;

	typedef struct {
		uintptr_t		data_ptr;
	} font_t;

	ErrorOr<void> init_video(int width, int height, const char *title);
	ErrorOr<void> deinit_video(void);

	ErrorOr<void> init_frame(void);
	ErrorOr<void> swap_buffers(void);

	bool should_close_window(void);

	// "pixels" as Big-Endian RGBA8888, from top-left to bottom-right.
	ErrorOr<texture_t *> create_bitmap_texture(u32 width, u32 height, u8 *pixels);

	ErrorOr<void> update_bitmap_texture(texture_t *tex, u32 width, u32 height, u8 *pixels);
	ErrorOr<void> update_bitmap_texture(texture_t *tex, u8 *pixels);
	ErrorOr<void> update_bitmap_texture(texture_t *tex);

	ErrorOr<void> draw_texture(texture_t *texture, float x, float y, float w, float h, float a, float t);

	void free_texture(texture_t *texture);

	ErrorOr<texture_t *> load_texture_from_file(const char *filepath);

	ErrorOr<void> draw_font(font_t *font, const char *text, float x, float y, float size, float spacing, color_t color);

	void free_font(font_t *font);

	ErrorOr<font_t *> load_font_from_file(const char *filepath);
};

#endif
