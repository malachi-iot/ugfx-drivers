extern "C" {

#include <gfx.h>
#include <string.h>

}

#include "board_SSD1306.h"
#include <frab/frab.h>
#include <ssd1306_i2c.hpp>

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


extern "C" void ssd1306_i2c_write_cmd(GDisplay *g, uint8_t cmd) 
{
    auto tx = i2c.get_tx_auto(SSD1306_I2C_ADDRESS);

    tx.write(OLED_CONTROL_BYTE_CMD_SINGLE);
    tx.write(cmd);
}

extern "C" void ssd1306_i2c_write_data(GDisplay *g, uint8_t* data, uint16_t length)
{
    auto tx = i2c.get_tx_auto(SSD1306_I2C_ADDRESS);

    tx.write(OLED_CONTROL_BYTE_DATA_STREAM);
    tx.write(data, length, false);
}