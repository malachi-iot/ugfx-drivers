#include <frab/spi.h>
#include <frab/gpio.h>

namespace frab = framework_abstraction;

static frab::layer1::SPI<SpiNum_HSPI> spi;
static frab::layer1::digital_out<4> pin_dc;

// NOTE: digital_out doesn't actually setup pin for output (artifact
// of still-undecided initialization scheme)

#include <gdisp/spi/ILI9341.hpp>