/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#define USE_I2C

#define SSD1306_REPEAT_START

#ifdef USE_I2C

#endif

void ssd1306_i2c_init_board(GDisplay *g);
void ssd1306_i2c_write_cmd(GDisplay *g, uint8_t cmd);
void ssd1306_i2c_write_data(GDisplay *g, uint8_t* data, uint16_t length);
void ssd1306_i2c_acquire_bus(GDisplay* g);
void ssd1306_i2c_release_bus(GDisplay* g);

// NOTE: Looks like special allocations need to happen for DMA, as described 
// here https://esp-idf.readthedocs.io/en/v2.0/api/peripherals/spi_master.html#transaction-data
static GFXINLINE void init_board(GDisplay *g) {
    ssd1306_i2c_init_board(g);
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
#ifdef SSD1306_REPEAT_START
	ssd1306_i2c_acquire_bus(g);
#endif
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
#ifdef SSD1306_REPEAT_START
	ssd1306_i2c_release_bus(g);
#endif
}

static GFXINLINE void write_cmd(GDisplay *g, uint8_t cmd)
{
    ssd1306_i2c_write_cmd(g, cmd);
}

static GFXINLINE void write_data(GDisplay *g, uint8_t* data, uint16_t length)
{
    ssd1306_i2c_write_data(g, data, length);
}

#ifdef __cplusplus
// close extern "C"
}
#endif

#endif /* _GDISP_LLD_BOARD_H */