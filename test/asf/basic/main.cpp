// Copied straight from pga-2
#include "start/atmel_start.h"

#include <estd/string.h>

#include "start/usb/class/cdc/device/cdcdf_acm.h"

#include "start/usb_start.h"
#include "start/rtos_start.h"

#include "mini-printf.h"

#include "usbdc.h"

#include "main.h"

#include <frab/gpio.h>


// NOTE: Fragile, buffer overflow happens easily - needs time to empty USB
// buffer
int printf(const char *fmt, ...)
{
    static CONSTEXPR int bufsize = CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ / 4;
    static     uint32_t usbd_cdc_buffer[bufsize];

    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf((char*)usbd_cdc_buffer, bufsize * 4, fmt, va);
    va_end(va);

    cdcdf_acm_write((uint8_t*)usbd_cdc_buffer, ret);
    return ret;
}


void spi_test();
void spi_setup();
void spi_shutdown();

using namespace framework_abstraction;

static layer0::digital_out<RED_LED> led_pin;

extern "C" int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	estd::layer1::string<32> hello = "hi2u";

    // example works, but is not needed for our cheap and nasty printf
    //cdcd_acm_example();

    bool led_toggle = false;
    int counter = 0;

    spi_setup();

    while (1) {
        led_pin = led_toggle = !led_toggle;
        spi_test();
        // give USB a moment to handle output before overwriting buffer
        delay_ms(50);
        printf("counter: %d\n", counter++);
        delay_ms(500);
    }
}
