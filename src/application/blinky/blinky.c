#include "blinky.h"
#include "driver/lsm6dso/lsm6dso.h"

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"

// example blinky task
void blinky_task(void *pvParameters)
{
    (void)pvParameters;

    // this runs forever
    for (;;)
    {
        // ------ onboarding task part 0.5 ------
        // toggle green led on/off each time this loop runs (which is connected to gpio PE10)
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);  // LED_R
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10); // LED_G
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11); // LED_B

        // delay for 500 ms
        vTaskDelay(pdMS_TO_TICKS(500));
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
