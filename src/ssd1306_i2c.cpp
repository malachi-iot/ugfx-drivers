extern "C" {

#include <gfx.h>
#include <string.h>

}

#include "board_SSD1306.h"
#include <frab/frab.h>
#include <board/ssd1306_i2c.hpp>

// lifted from https://github.com/yanbe/ssd1306-esp-idf-i2c
// Control byte
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

// This can be modified in a lot of places, probably declaring it
// in gfxconf.h is most convenient - note multiple displays not
// yet supported
#ifndef SSD1306_I2C_ADDRESS
#define SSD1306_I2C_ADDRESS   0x3C  // 011110+SA0+RW - 0x3C or 0x3D
// Address for 128x32 is 0x3C
// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)
#endif

// TODO: put these into frab itself, after resolving how it interplays with dummy i2c 
template <class TOut>
inline TOut& operator << (TOut& out, uint8_t value)
{
    out.write(value);
    return out;
}

extern "C" void ssd1306_i2c_init_board(GDisplay *g)
{
    // FIX: Last remnant of ESP32 specificity
    i2c.config(ESP32_FREQ_HZ);
}

#ifdef SSD1306_REPEAT_START
// declare tx_t as a i2c transaction type which does not auto-send stop on destruction
typedef decltype(i2c.get_tx<false>(0)) tx_t;

// use placement helper to manage construction/destruction of i2c transaction 
// in a static global context
static framework_abstraction::experimental::placement_helper<tx_t> _tx;

// helper flag so that we can enter START condition immediately
// NOTE: ironically, *actual* command queued systems like ESP-IDF won't
// send START condition immediately because ... yes, it's queued
static bool command_queued;

extern "C" void ssd1306_i2c_acquire_bus(GDisplay* g)
{
    command_queued = false;
    _tx.construct();
}

extern "C" void ssd1306_i2c_release_bus(GDisplay* g)
{
    _tx.get().stop();
    _tx.destroy();
}

typedef tx_t& tx_handle;

static inline tx_handle get_tx()
{
    if(command_queued)
    {
        // if queued, sends command (destructor)
        // then, restarts the TX and sends a START
        // no STOP is sent, thus holding the bus 
        _tx.recycle();
    }
    else
        command_queued = true;

    tx_t& tx = _tx;
    tx.addr(SSD1306_I2C_ADDRESS);
    return tx;
}
#else
typedef tx_t tx_handle;

static inline tx_handle get_tx()
{
    return i2c.get_tx(SSD1306_I2C_ADDRESS);
}
#endif

extern "C" void ssd1306_i2c_write_cmd(GDisplay *g, uint8_t cmd) 
{
    tx_handle tx = get_tx();

    tx << OLED_CONTROL_BYTE_CMD_SINGLE << cmd;
}

extern "C" void ssd1306_i2c_write_data(GDisplay *g, uint8_t* data, uint16_t length)
{
    tx_handle tx = get_tx();

    tx << OLED_CONTROL_BYTE_DATA_STREAM;
    tx.write(data, length, false);
}