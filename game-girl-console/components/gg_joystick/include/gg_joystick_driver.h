#include "esp_err.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* Assigns ADC channels to the Joystick's X and Y axes. */
#define JOYSTICK_X_AXIS ADC1_CHANNEL_1
#define JOYSTICK_Y_AXIS ADC1_CHANNEL_2

/* Assigns a GPIO with the Joystick Select Button. */
#define JOYSTICK_SELECT_BUTTON  GPIO_NUM_14

class JoystickDriver {
public:

    /*!
     * @brief   The initializaton functon to start up any necessary peripherals and resources needed
     *              for the Joystck Driver to operate.
     *
     * @retval  ESP_OK      Returned if the initialization was successful.
     * @retval  ESP_FAIL    Returned if the initialization failed.
     */
    esp_err_t init();

    /*!
     * @brief   Reads the raw values of the X and Y axis ADC channels.
     *
     * @param[out]          xAxis   The X-axis ADC channel raw value.
     * @param[out]          yAxis   The Y-axis ADC channel raw value.
     *
     * @retval  ESP_OK                  Returned if the reading was successful.
     * @retval  ESP_FAIL                Returned if the reading failed.  
     */
    esp_err_t retrieveRawJoystickValues(uint16_t &xAxis, uint16_t &yAxis);

    /*!
     * @brief   Reads the select button GPIO of the Joystick.
     *
     * @retval  ESP_OK    Returned if the reading was successful.
     */
    esp_err_t retrieveSelectButtonGpioLevel(uint8_t &selectButtonGpioLevel);
};
