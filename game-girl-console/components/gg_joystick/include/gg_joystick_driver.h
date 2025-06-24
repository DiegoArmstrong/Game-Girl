#include "esp_err.h"

class JoystickDriver {
public:

    /*
     * @brief   The initializaton functon to start up any necessary peripherals and resources needed
                    for the Joystck Driver to operate.
     *
     * @retval  ESP_OK      Returned if the initialization was successful.
     * @retval  ESP_FAIL    Returned if the initialization failed.
     */
    esp_err_t init();
};
