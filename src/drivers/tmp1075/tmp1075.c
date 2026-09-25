#include "tmp1075.h"

#include "main.h"
#include "stm32c0xx_hal.h"

// Register map
#define REG_TEMP 0x00U
#define REG_CONFIG 0x01U
#define REG_T_LOW 0x02U
#define REG_T_HIGH 0x03U

// Datasheet Table 7-2: A2=0, A1=0, A0=0 -> device address=0b1001000 (0x48)
static const uint16_t I2C_DEV_ADDR = 0x48U;

// Datasheet 6.5: 1 LSB from the raw 12-bit reading = 0.0625°C
static const float CELSIUS_PER_LSB = 0.0625f;

// The TMP1075 is connected to I2C1 on the mcu
extern I2C_HandleTypeDef hi2c1;

w_status_t tmp1075_init(void) {
	// Default config is fine for now, nothing else needed
	return W_SUCCESS;
}

w_status_t tmp1075_get_temperature(float *temperature_c) {
	uint8_t raw_data[2];

	// Validate arguments
	if (temperature_c == NULL) {
		return W_FAILURE;
	}

	// Read 2 bytes from the temperature register
	if (HAL_I2C_Mem_Read(&hi2c1,
						 I2C_DEV_ADDR << 1U, // Shift 7-bit addr to be 8-bit for HAL
						 REG_TEMP,
						 I2C_MEMADD_SIZE_8BIT,
						 raw_data,
						 sizeof(raw_data),
						 100U) != HAL_OK) {
		return W_FAILURE;
	}

	// Concatenate the 2 bytes into a 16-bit signed integer
	const int16_t raw_temperature = ((uint16_t)raw_data[0] << 8U) | raw_data[1];
	// Datasheet 7.5.1.1: only the first 12 bits are used to indicate temperature, so shift away the
	// unused 4 bits
	*temperature_c = (float)(raw_temperature >> 4) * CELSIUS_PER_LSB;

	return W_SUCCESS;
}
