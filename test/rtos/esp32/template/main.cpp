#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern "C" void demo(void* pvParameters);

extern "C" void app_main()
{
    xTaskCreate(demo, "demoTask", 2048, NULL, 2, NULL);
}