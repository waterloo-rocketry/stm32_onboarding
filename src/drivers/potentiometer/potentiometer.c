#include "potentiometer.h"

#include "main.h"

// The board has 3.3V reference voltage for the mcu
static const float ADC_MAX_VOLTAGE = 3.3f;
// stm32c0 has a 12-bit ADC
static const uint32_t ADC_MAX_COUNTS = 0xFFF;

extern ADC_HandleTypeDef hadc1;

w_status_t potentiometer_init(void) {
	if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK) {
		return W_FAILURE;
	}
	return W_SUCCESS;
}

w_status_t potentiometer_get_voltage(float *voltage) {
	// Validate arguments
	if (voltage == NULL) {
		return W_FAILURE;
	}

	// Start the ADC conversion
	if (HAL_ADC_Start(&hadc1) != HAL_OK) {
		return W_FAILURE;
	}

	// Wait up to 100ms for the conversion to complete
	if (HAL_ADC_PollForConversion(&hadc1, 100U) != HAL_OK) {
		(void)HAL_ADC_Stop(&hadc1);
		return W_FAILURE;
	}

	// Read the ADC conversion result
	const uint32_t adc_counts = HAL_ADC_GetValue(&hadc1);

	if (HAL_ADC_Stop(&hadc1) != HAL_OK) {
		return W_FAILURE;
	}

	// Convert the raw ADC counts value to voltage. Interpret the adc counts reading as a proportion
	// of the maximum counts, then scale to the max voltage.
	*voltage = ((float)adc_counts / (float)ADC_MAX_COUNTS) * ADC_MAX_VOLTAGE;

	return W_SUCCESS;
}
