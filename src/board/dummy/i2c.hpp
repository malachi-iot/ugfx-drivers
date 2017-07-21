#include <frab/shim/i2c.h>

framework_abstraction::layer1::i2c i2c;

// FIX: Get rid of this dangling dependency
#define ESP32_FREQ_HZ       1000000
