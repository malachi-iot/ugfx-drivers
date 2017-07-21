# Board folder

In here we have board-specific header files.  Even though the frameworks have
been abstracted, the specific i2c/spi ports and configurations will still vary
for the hardware you've got.

The default board configuration is "dummy" or a noop.  This has a few benefits:

a) All board drivers can compile and link at all times with nothing but compile time
   overhead
b) Activating and configuring a board are one step, copy or link to or create the appropriate .hpp file in your application folder (effectively overriding dummy .hpp file)