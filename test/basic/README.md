# Scope

This test serves primarily to ensure code is compiling
Also does "basics gdisp" test from uGFX

# TODO:

1.  PGESP-2 brought in lots of FreeRTOS shim header files.  What I'd prefer here is
    to add the ESP-IDF FreeRTOS include path

# Notes

FreeRTOS_Shim almost works, but uGFX itself can't find header files so we're back to scattering
shim files around the main source, or forcing ESP-IDF FreeRTOS pathin to be included.  The
latter may prove tricky as platformio may put ESP-IDF in a potentially non-deterministic
location

