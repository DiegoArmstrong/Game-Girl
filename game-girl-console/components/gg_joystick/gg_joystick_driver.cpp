#include "gg_joystick_driver.h"
#include "driver/adc.h"
#include "esp_log.h"

static const char* TAG = "JoystickDriver";

/*
* @brief   The initializaton functon to start up any necessary perpherals and resources needed
*            for the Joystck Driver to operate.
*
* @retval  ESP_OK      Returned if the initialization was successful.
* @retval  ESP_FAIL    Returned if the initialization failed.
*/
esp_err_t JoystickDriver::init() {
    esp_err_t ret = ESP_OK;

    /* Configure the ADC channel and attenuation. */
    ret = adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_12);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the ADC1 channel attenuation within JoystickDriver::init().");
        goto err;
    }

    /* Configure the ADC channel bit width. */
    ret = adc1_config_width(ADC_WIDTH_BIT_12);
    if(ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure the bit width of ADC1 within JoystickDriver::init().");
        goto err;
    }

    return ESP_OK;

err:
    return ESP_FAIL;
}
