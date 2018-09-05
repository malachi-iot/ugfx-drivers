To start with, we will bind this to a very specific flavor of atmel board

Choosing adafruit feather + SPI TFT display

Eventually we can decouple these things with judicious application of frab + Cmake

Use:

`cmake -DCMAKE_TOOLCHAIN_FILE=../tools/atmel/gcc-samd21g18a.cmake ..`

from a build/ folder
