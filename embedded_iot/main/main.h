#ifndef MAIN_H_
#define MAIN_H_

// hall drivers
#include "led.h"
#include "button.h"
#include "dc_motor.h"
#include "TCRT5000.h"
#include "ultrasonic.h"
#include "pot.h"
#include "pid.h"
#include "MPU6050.h"

// mcu drivers
#include "MQTT.h"
#include "NVS.h"
#include "WiFi.h"

extern const char *TAG;

// WiFi configurations
#define ssid                    "Mohamed Fathy"
#define password                "341978341978"

// MQTT configurations
#define mqtt_broker             "mqtt://192.168.100.25"
#define mqtt_port               1883

// topic iot 
#define topic_forward           "/smart_car/control/forward"
#define topic_backward          "/smart_car/control/backward"
#define topic_right             "/smart_car/control/right"
#define topic_left              "/smart_car/control/left"
#define topic_stop              "/smart_car/control/stop"

#define topic_speed_right       "/smart_car/control/speed/right"
#define topic_speed_left        "/smart_car/control/speed/left"

#define topic_distance_forward  "/smart_car/monitor/distance/forward"
#define topic_distance_backward "/smart_car/monitor/distance/backward"

#define topic_track_tcrt_right  "/smart_car/monitor/track/right"
#define topic_track_tcrt_left   "/smart_car/monitor/track/left"

#define topic_rpy_mpu6050_roll  "/smart_car/monitor/rpy/roll"
#define topic_rpy_mpu6050_pitch "/smart_car/monitor/rpy/pitch"
#define topic_rpy_mpu6050_yaw   "/smart_car/monitor/rpy/yaw"
#define topic_acc_mpu6050_x     "/smart_car/monitor/acc/x"
#define topic_acc_mpu6050_y     "/smart_car/monitor/acc/y"
#define topic_acc_mpu6050_z     "/smart_car/monitor/acc/z"
#define topic_temp_mpu6050      "/smart_car/monitor/temp/mpu6050" 

// prototyping functions
void setup_wifi();
void setup_mqtt();
void init_hw();

#endif
