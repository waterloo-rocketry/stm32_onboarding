#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdint.h>

#include "rocketlib/include/common.h"

w_status_t potentiometer_init(void);

/**
 * @brief Read the current potentiometer voltage.
 * @param voltage_v Pointer to store the measured voltage in volts.
 * @return W_SUCCESS if the voltage was read successfully, W_FAILURE otherwise.
 */
w_status_t potentiometer_get_voltage(float *voltage);

#endif // POTENTIOMETER_H