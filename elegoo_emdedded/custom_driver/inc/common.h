#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include  "mqtt_client.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

enum class status: uint8_t {
    LOW, HIGH    
};


#endif