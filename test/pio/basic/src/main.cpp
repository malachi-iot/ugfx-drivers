#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern "C" void demo(void* pvParameters);

extern "C" void app_main()
{
    // FIX: 90% sure vTaskStartScheduler already started by the time we get here
    // but doublecheck

    xTaskCreate(demo, "demoTask", 2048, NULL, 2, NULL);
}