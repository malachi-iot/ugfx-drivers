#include <frab/i2c.h>

#define SSD1306_I2C_BUS          I2C_NUM_0
// Not sure if there is some arduino pin mapping going on
#define ESP32_SDA1          GPIO_NUM_5
#define ESP32_SCL1          GPIO_NUM_4
#define ESP32_FREQ_HZ       1000000
//#define ESP32_I2C_BUF_DISABLE_FLAG  0

framework_abstraction::layer1::i2c<SSD1306_I2C_BUS, ESP32_SDA1, ESP32_SCL1> i2c;
