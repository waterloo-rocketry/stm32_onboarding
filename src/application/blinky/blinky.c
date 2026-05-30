#include "blinky.h"
#include "driver/lsm6dso/lsm6dso.h"

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"

// example blinky task
void blinky_task(void *pvParameters)
{
    (void)pvParameters;

    int time = 0;

    // this runs forever
    for (;;)
    {
        // resets the time to 0 at the LCM of 400, 500, and 600 ms, which is 6000 ms
        if (time == 6000) 
        {
            time = 0;
        }

        // ------ onboarding task part 0.5 ------
        // toggle green led on/off every 500 ms (which is connected to gpio PE10)
        if (time % 500 == 0)
        {
            HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
        }
        
        // toggle red led every 400 ms
        if (time % 400 == 0)
        {
            HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
        }


        // toggle blue led every 600 ms
        if (time % 600 == 0)
        {
            HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
        }

        // delay for 100 ms
        vTaskDelay(pdMS_TO_TICKS(100));
        time += 100;
        // --------------------------------------

        // ------ onboarding task part 1 ------
        // check LSM6DSO is alive
        w_status_t status = lsm6dso_check_sanity();
        if (status != W_SUCCESS)
        {
            // error !
        }
    }
}
