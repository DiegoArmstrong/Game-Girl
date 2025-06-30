#include "gg_joystick_driver.h"

static const char* TAG = "JoystickDriver";

/*!
 * @brief   The initializaton functon to start up any necessary perpherals and resources needed
 *            for the Joystck Driver to operate.
 *
 * @retval  ESP_OK      Returned if the initialization was successful.
 * @retval  ESP_FAIL    Returned if the initialization failed.
 */
esp_err_t JoystickDriver::init() {
    esp_err_t ret = ESP_OK;
    gpio_config_t selectButtonConfig = {};

    /* Configure the X-axis ADC channel and attenuation. */
    ret = adc1_config_channel_atten(JOYSTICK_X_AXIS, ADC_ATTEN_DB_12);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the X-axis channel attenuation within JoystickDriver::init().");
        goto err;
    }

    /* Configure the Y-axis ADC channel and attenuation. */
    ret = adc1_config_channel_atten(JOYSTICK_Y_AXIS, ADC_ATTEN_DB_12);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the Y-axis ADC channel attenuation within JoystickDriver::init().");
        goto err;
    }

    /* Configure the ADC channel bit width. */
    ret = adc1_config_width(ADC_WIDTH_BIT_12);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the bit width of ADC1 within JoystickDriver::init().");
        goto err;
    }

    /* Configure the Joystick Select Button. */
    selectButtonConfig.intr_type = GPIO_INTR_DISABLE;
    selectButtonConfig.mode = GPIO_MODE_INPUT;
    selectButtonConfig.pin_bit_mask = 1ULL << JOYSTICK_SELECT_BUTTON;
    selectButtonConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    selectButtonConfig.pull_up_en = GPIO_PULLUP_ENABLE;

    ret = gpio_config(&selectButtonConfig);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the Joystick Select Button GPIO within JoystickDriver::init().");
        goto err;
    }

    return ESP_OK;

err:
    return ESP_FAIL;
}

/*!
 * @brief   Reads the raw values of the X and Y axis ADC channels.
 *
 * @param[out]          xAxis   The X-axis ADC channel raw value.
 * @param[out]          yAxis   The Y-axis ADC channel raw value.
 *
 * @retval  ESP_OK                  Returned if the reading was successful.
 * @retval  ESP_FAIL                Returned if the reading failed.  
 */
esp_err_t JoystickDriver::retrieveRawJoystickValues(uint16_t &xAxis, uint16_t &yAxis) {
    esp_err_t ret = ESP_OK;

    /* Get the raw readings. */
    xAxis = adc1_get_raw(JOYSTICK_X_AXIS);
    yAxis = adc1_get_raw(JOYSTICK_Y_AXIS);

    return ESP_OK;
}

/*!
 * @brief   Reads the select button GPIO of the Joystick.
 *
 * @retval  ESP_OK    Returned if the reading was successful.
 */
esp_err_t retrieveSelectButtonGpioLevel(uint8_t &selectButtonGpioLevel) {
    esp_err_t ret = ESP_OK;

    selectButtonGpioLevel = gpio_get_level(JOYSTICK_SELECT_BUTTON);

    return ESP_OK;
}
