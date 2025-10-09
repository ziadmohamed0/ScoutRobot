#include "esp_log.h"
#include "dc_motor.h"
#include "TCRT5000.h"
#include "ultrasonic.h"
#include "MPU6050.h"

static const char* TAG = "MAIN_MPU";
std::vector<gpio_num_t> motorPins = {
    GPIO_NUM_16,
    GPIO_NUM_17,
    GPIO_NUM_18,
    GPIO_NUM_19

};
extern "C" void app_main(void) {
    const float dt = 0.01f; // for imu
    dc_motor m1(motorPins);
    while (true) {
        m1.dc_move(DC_MOTOR_DIRECTION::forward);
        vTaskDelay(pdMS_TO_TICKS(1500));
        m1.dc_move(DC_MOTOR_DIRECTION::backward);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }

}
