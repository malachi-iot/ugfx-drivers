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

extern "C" void ssd1306_i2c_init_board(GDisplay *g)
{
    // FIX: Last remnant of ESP32 specificity
    i2c.config(ESP32_FREQ_HZ);
}

#ifdef SSD1306_REPEAT_START
// FIX: Incorrect, this flavor auto-queues a stop before send,
// we'll need the flavor that doesn't do that
typedef decltype(i2c.get_tx(0)) tx_t;

static framework_abstraction::experimental::placement_helper<tx_t> _tx;
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

static inline tx_t& repeat_start_handler()
{
    tx_t& tx = _tx.get();
    if(command_queued)
    {
        // if queued, sends command (destructor)
        // then, restarts the TX and sends a START
        // no STOP is sent, thus holding the bus 
        _tx.recycle();
    }
    else
    {
        command_queued = true;
    }
    tx.addr(SSD1306_I2C_ADDRESS);
    return tx;
}

#endif

extern "C" void ssd1306_i2c_write_cmd(GDisplay *g, uint8_t cmd) 
{
#ifdef SSD1306_REPEAT_START
    tx_t& tx = repeat_start_handler();
#else
    auto tx = i2c.get_tx(SSD1306_I2C_ADDRESS);
#endif

    tx.write(OLED_CONTROL_BYTE_CMD_SINGLE);
    tx.write(cmd);
}

extern "C" void ssd1306_i2c_write_data(GDisplay *g, uint8_t* data, uint16_t length)
{
#ifdef SSD1306_REPEAT_START
    tx_t& tx = repeat_start_handler();
#else
    auto tx = i2c.get_tx(SSD1306_I2C_ADDRESS);
#endif

    tx.write(OLED_CONTROL_BYTE_DATA_STREAM);
    tx.write(data, length, false);
}