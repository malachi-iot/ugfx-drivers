#include <frab/spi.h>

// some clues how we should do this here https://github.com/fcayci/stm32f1-uGFX but quite low level
// more clues https://community.ugfx.io/topic/156-ili9341-spi-stm32f103/
// more clues https://community.ugfx.io/topic/1000-generic-board-file-for-ili9341-and-the-arduino-ide-based-on-adadruits-generic-library-supporting-different-boards/

extern "C" {

#include <gfx.h>
#include <string.h>

}

extern "C" void init_ili9341_board(GDisplay *g)
{

}


extern "C" void post_init_ili9341_board(GDisplay *g)
{

}

extern "C" void setpin_ili9341_reset(GDisplay *g, bool_t state)
{

}


extern "C" void set_ili9341_backlight(GDisplay *g, uint8_t percent)
{

}


extern "C" void acquire_ili9341_bus(GDisplay *g);
extern "C" void release_ili9341_bus(GDisplay *g);
extern "C" void write_ili9341_index(GDisplay *g, uint16_t index);
extern "C" void write_ili9341_data(GDisplay *g, uint16_t data);
extern "C" void ili9341_setreadmode(GDisplay *g);
extern "C" void ili9341_setwritemode(GDisplay *g);
extern "C" uint16_t ili9341_read_data(GDisplay *g);