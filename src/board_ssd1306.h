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

#define SSD_1306_TAG "SSD1306"

#ifdef USE_I2C

#endif


// TODO: Turn these back into static GFXINLINE because I'm pretty sure
//  that's how multi-display systems stay discrete from one another
// TODO: try to associate this with GDisplay if convenient
// NOTE: Looks like special allocations need to happen for DMA, as described 
// here https://esp-idf.readthedocs.io/en/v2.0/api/peripherals/spi_master.html#transaction-data
void init_board(GDisplay *g);

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

void write_cmd(GDisplay *g, uint8_t cmd);

void write_data(GDisplay *g, uint8_t* data, uint16_t length);

#ifdef __cplusplus
// close extern "C"
}
#endif

#endif /* _GDISP_LLD_BOARD_H */