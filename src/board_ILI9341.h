#pragma once

/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

void init_ili9341_board(GDisplay *g);
void post_init_ili9341_board(GDisplay *g);
void setpin_ili9341_reset(GDisplay *g, bool_t state);
void set_ili9341_backlight(GDisplay *g, uint8_t percent);
void acquire_ili9341_bus(GDisplay *g);
void release_ili9341_bus(GDisplay *g);
void write_ili9341_index(GDisplay *g, uint16_t index);
void write_ili9341_data(GDisplay *g, uint16_t data);
void ili9341_setreadmode(GDisplay *g);
void ili9341_setwritemode(GDisplay *g);
uint16_t ili9341_read_data(GDisplay *g);

static GFXINLINE void init_board(GDisplay *g) {
	init_ili9341_board(g);
}

static GFXINLINE void post_init_board(GDisplay *g) {
	post_init_ili9341_board(g);
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	acquire_ili9341_bus(g);
}

static GFXINLINE void release_bus(GDisplay *g) {
	release_ili9341_bus(g);
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index) {
	write_ili9341_index(g, index);
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data) {
	write_ili9341_data(g, data);
}

static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g) {
	(void) g;
	return 0;
}

#endif /* _GDISP_LLD_BOARD_H */
