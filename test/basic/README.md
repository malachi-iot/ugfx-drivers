# Scope

This test serves primarily to ensure code is compiling
Also does "basics gdisp" test from uGFX

# TODO:

1.  PGESP-2 brought in lots of FreeRTOS shim header files.  What I'd prefer here is
    to add the ESP-IDF FreeRTOS include path
2.  Document FreeRTOS (and even uGFX to a minor degree) path fiddling/shimming
3.  Move gdisp_lld_config.h to proper location if we can (the one in https://github.com/fredizzimo/uGFX/blob/master/drivers/gdisp/SSD1306/gdisp_lld_config.h should be sufficient if we can reference that directly)

# Notes

FreeRTOS_Shim almost works, but uGFX itself can't find header files so we're back to scattering
shim files around the main source, or forcing ESP-IDF FreeRTOS pathin to be included.  The
latter may prove tricky as platformio may put ESP-IDF in a potentially non-deterministic
location

gdisp_lld_config.h actually belongs within the driver code portion, it's only out here
because PGESP-2 had it in a similar location
reference: https://github.com/fredizzimo/uGFX/blob/master/drivers/gdisp/SSD1306/gdisp_lld_config.h