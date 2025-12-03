#ifndef COMMON_H_
#define COMMON_H_

// c++ library 
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <mutex>
#include <cstddef>

// memory
#include "esp_netif.h"
#include "nvs_flash.h"

// wireless communication 
#include "esp_wifi.h"
#include "esp_http_client.h"
extern "C" {
    #include "mqtt_client.h"
}
// wired communication 
#include "driver/i2c_master.h"  
#include "driver/i2c_slave.h"

// timers
#include "esp_timer.h"

// pwm
#include "driver/mcpwm_prelude.h"
#include "driver/ledc.h" 

// gpio
#include "driver/gpio.h"

// adc
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

// freeRtos
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"


// esp32 systems
#include "esp_log.h"
#include "esp_event.h"
#include "esp_system.h"

// types
enum class state { 
    Low, High 
};

#endif