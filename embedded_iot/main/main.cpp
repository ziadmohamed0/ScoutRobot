/**
 * @file main.cpp
 * @author Ziad Mohamed Fathy
 * @brief esp32 suit inputs and publish data to mqtt broker
 * @version 0.1
 * @date 2025-10-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "main.h"

const char *TAG = "main_task";

std::vector<gpio_num_t> motro_pins = {
    GPIO_NUM_16,
    GPIO_NUM_17,
    GPIO_NUM_18,
    GPIO_NUM_19
};

WiFiManager     *wifi = nullptr;
MQTTClient      *mqtt = nullptr;
NVS             *nvs  = nullptr; 

dc_motor        *l298           = nullptr;
ultrasonic      *ultra_forward  = nullptr;
ultrasonic      *ultra_backward = nullptr;
tcrt_sensor     *tcrt_right     = nullptr;
tcrt_sensor     *tcrt_left      = nullptr;
MPU6050         *mpu            = nullptr;

int g_forward = 0;
int g_backward = 0;
int g_right = 0;
int g_left = 0;
int g_stop = 0;

void setup_wifi();
void setup_mqtt();
void init_hw();

extern "C" void app_main(void) {
    nvs = new NVS();
    setup_wifi();
    setup_mqtt();
    init_hw();
    
    TickType_t last_wake_time = xTaskGetTickCount();
    const TickType_t update_period = pdMS_TO_TICKS(20);

    while(true) {
        float forward_ultra = ultra_forward->readDistance();
        float backward_ultra = ultra_backward->readDistance();
        bool read_tcrt_right = tcrt_right->readDigital();
        bool read_tcrt_left = tcrt_left->readDigital();
        
        mpu->updateAngles(0.02);
        float roll = mpu->getRoll();
        float pitch = -mpu->getPitch();
        float yaw = mpu->getYaw();
        float temp = mpu->readTemprature();
        float accx= mpu->getAccx();
        float accy= mpu->getAccy();
        float accz= mpu->getAccz();

        if(g_forward == 1) {
            l298->dc_move(DC_MOTOR_DIRECTION::forward);
            g_forward = 0;
        }

        if(g_backward == 1) {
            l298->dc_move(DC_MOTOR_DIRECTION::backward);
            g_backward = 0;
        }

        if(g_right == 1) {
            l298->dc_move(DC_MOTOR_DIRECTION::right);
            g_right = 0;
        }

        if(g_left == 1) {
            l298->dc_move(DC_MOTOR_DIRECTION::left);
            g_left = 0;
        }
        
        if(g_stop == 1) {
            l298->dc_move(DC_MOTOR_DIRECTION::stop);
            g_stop = 0;
        }
        
        mqtt->publish(topic_distance_forward, std::to_string(forward_ultra));
        mqtt->publish(topic_distance_backward, std::to_string(backward_ultra));
        mqtt->publish(topic_track_tcrt_right, std::to_string(read_tcrt_right));
        mqtt->publish(topic_track_tcrt_left, std::to_string(read_tcrt_left));
        mqtt->publish(topic_rpy_mpu6050_roll, std::to_string(roll));
        mqtt->publish(topic_rpy_mpu6050_pitch, std::to_string(pitch));
        mqtt->publish(topic_rpy_mpu6050_yaw, std::to_string(yaw));
        mqtt->publish(topic_acc_mpu6050_x, std::to_string(accx));
        mqtt->publish(topic_acc_mpu6050_y, std::to_string(accy));
        mqtt->publish(topic_acc_mpu6050_z, std::to_string(accz));

        mqtt->publish(topic_temp_mpu6050, std::to_string(temp));
        
        vTaskDelayUntil(&last_wake_time, update_period);
    }
}

void setup_wifi() {
    wifi = new WiFiManager();
    wifi->on_connected([](std::string ip) {
        ESP_LOGI(TAG, "WiFi connected ip: %s", ip.c_str());
    });
    wifi->on_disconnected([](){
        ESP_LOGW(TAG, "WiFi Disconnected !");
    });
    wifi->init_sta(ssid, password, 5);
    wifi->connect();
}

void setup_mqtt() {
    mqtt = new MQTTClient();
    MQTTConfig cfg;
    cfg.broker_uri  = mqtt_broker;
    cfg.port        = mqtt_port;
    cfg.client_id = "ESP32_test_" + std::to_string(rand() % 10000);
    cfg.keepalive = 60;
    
    mqtt->init(cfg);
    
    mqtt->on_connected([&]() {
        ESP_LOGI(TAG, "Connected to MQTT Broker");
        mqtt->subscribe(topic_forward);
        mqtt->subscribe(topic_backward);
        mqtt->subscribe(topic_right);
        mqtt->subscribe(topic_left);
        mqtt->subscribe(topic_stop);
    });
    
    mqtt->on_message([&](std::string topic, std::string msg) {
        ESP_LOGI(TAG, "Received: %s -> %s", topic.c_str(), msg.c_str());
        
        int value = std::stoi(msg);
        
        if(topic == topic_forward) {
            g_forward = value;
        }
        else if(topic == topic_backward) {
            g_backward = value;
        }
        else if(topic == topic_right) {
            g_right = value;
        }
        else if(topic == topic_left) {
            g_left = value;
        }
        else if(topic == topic_stop) {
            g_stop = value;
        }
    });
    
    mqtt->connect();
    
    while (!mqtt->is_connected()) {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void init_hw() {
    l298 = new dc_motor(motro_pins); 
    ultra_forward = new ultrasonic(GPIO_NUM_32, GPIO_NUM_33);
    ultra_backward = new ultrasonic(GPIO_NUM_27, GPIO_NUM_26);
    tcrt_right = new tcrt_sensor(GPIO_NUM_25);
    tcrt_left = new tcrt_sensor(GPIO_NUM_14);
    mpu = new MPU6050(GPIO_NUM_21, GPIO_NUM_22);
}
