#ifndef TMP1075_H
#define TMP1075_H

#include <stdint.h>

#include "rocketlib/include/common.h"

w_status_t tmp1075_init(void);

/**
 * @brief Read the current temperature from the TMP1075.
 * @param temperature_c Pointer to store the temperature in degrees Celsius.
 * @return W_SUCCESS if the temperature was read successfully, W_FAILURE otherwise.
 */
w_status_t tmp1075_get_temperature(float *temperature_c);

#endif // TMP1075_H