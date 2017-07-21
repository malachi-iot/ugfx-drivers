#include "freertos/task.h"

// FIX: super hacky compatibility layer
extern portMUX_TYPE _hack_mux;

#undef taskENTER_CRITICAL
#define taskENTER_CRITICAL()  portENTER_CRITICAL(&_hack_mux)

#undef taskEXIT_CRITICAL
#define taskEXIT_CRITICAL()   portEXIT_CRITICAL(&_hack_mux)