#include <frab/spi.h>

// some clues how we should do this here https://github.com/fcayci/stm32f1-uGFX but quite low level
// more clues https://community.ugfx.io/topic/156-ili9341-spi-stm32f103/
// more clues https://community.ugfx.io/topic/1000-generic-board-file-for-ili9341-and-the-arduino-ide-based-on-adadruits-generic-library-supporting-different-boards/
// adapting code from https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.cpp (thanks MIT license!)

extern "C" {

#include <gfx.h>
#include <string.h>

}

inline static void ili_cmd(uint8_t cmd)
{
    pin_dc.write(false);
    spi.write8(cmd);
    pin_dc.write(true);
}

template <int N>
inline static void spi_write(uint8_t (& buffer) [N])
{

}

template <int N>
inline static void ili_cmd(uint8_t cmd, uint8_t (& buffer) [N])
{
    ili_cmd(cmd);
    spi.write(buffer, N);
}

/* would use this, but don't fully trust initializer list in Arduino environments
   yet
inline static void spi_write(initializer_list<uint8_t> l)
{

} */

extern "C" void init_ili9341_board(GDisplay *g)
{
    pin_dc.init_for_output_exp();
    spi.begin(); // more of an init really. consider 'init' instead

    // TODO: issue a reset on reset pin

/* nevermind, looks like gdisp_lld_ILI9341 does this too
    {
        uint8_t data[] = { 0x03, 0xB0, 0x02 };
        ili_cmd(0xEF, data);
    }
    {
        uint8_t data[] = { 0x00, 0xC1, 0x30 };
        ili_cmd(0xCF, data);
    }
    {
        uint8_t data[] = { 0x64, 0x03, 0x12, 0x81 };
        ili_cmd(0xED, data);
    }
    {
        uint8_t data[] = { 0x85, 0x00, 0x78 };
        ili_cmd(0xE8, data);
    }
    {
        uint8_t data[] = { 0x39, 0x2C, 0x00, 0x34, 0x02 };
        ili_cmd(0xCB, data);
    } */
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


extern "C" void acquire_ili9341_bus(GDisplay *g)
{
    // amounts largely to setting CS pin, but not sure how to do that yet
    // for ESP
}


extern "C" void release_ili9341_bus(GDisplay *g)
{

}

extern "C" void write_ili9341_index(GDisplay *g, uint16_t index)
{
    // near as I can tell, index are all 8 bit values for this board
    ili_cmd(index);
}


extern "C" void write_ili9341_data(GDisplay *g, uint16_t data)
{
    spi.write8(data);
}


extern "C" void ili9341_setreadmode(GDisplay *g);
extern "C" void ili9341_setwritemode(GDisplay *g);
extern "C" uint16_t ili9341_read_data(GDisplay *g);