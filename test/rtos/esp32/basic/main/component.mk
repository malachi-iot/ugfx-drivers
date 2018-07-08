# conf for general configuration
# gdisp assists with specific displayer driver selection (especially since we aren't using uGFX build)
# shim to assist with ESP32's nesting of FreeRTOS #includes
COMPONENT_ADD_INCLUDEDIRS := conf conf/gdisp
COMPONENT_SRCDIRS += conf/gdisp