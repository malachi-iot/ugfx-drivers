extern "C" {

#include <gfx.h>
#include <string.h>

}

#include "board_SSD1306.h"
#include <frab/i2c.h>
#include <frab/frab.h>

// lifted from https://github.com/yanbe/ssd1306-esp-idf-i2c
// Control byte
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

#define SSD1306_I2C_BUS          I2C_NUM_0
// Not sure if there is some arduino pin mapping going on
#define ESP32_SDA1          GPIO_NUM_5
#define ESP32_SCL1          GPIO_NUM_4
#define ESP32_FREQ_HZ       1000000
//#define ESP32_I2C_BUF_DISABLE_FLAG  0

// Pulling from Adafruit lib, but not sure our D-Duino clone *actually* uses I2C
// for the SSD
#define SSD1306_I2C_ADDRESS   0x3C  // 011110+SA0+RW - 0x3C or 0x3D
// Address for 128x32 is 0x3C
// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)


namespace frab = framework_abstraction;

frab::layer1::i2c<SSD1306_I2C_BUS, ESP32_SDA1, ESP32_SCL1> i2c;


extern "C" void init_board(GDisplay *g)
{
    i2c.config(ESP32_FREQ_HZ);
}


extern "C" void write_cmd(GDisplay *g, uint8_t cmd) 
{
    auto tx = i2c.tx_begin_autocommit_experimental(SSD1306_I2C_ADDRESS);

    tx.write(OLED_CONTROL_BYTE_CMD_SINGLE);
    tx.write(cmd);
}

extern "C" void write_data(GDisplay *g, uint8_t* data, uint16_t length)
{
    auto tx = i2c.tx_begin_autocommit_experimental(SSD1306_I2C_ADDRESS);

    tx.write(OLED_CONTROL_BYTE_DATA_STREAM);
    tx.write(data, length, false);
}