#ifndef MQTT_H_
#define MQTT_H_

#include <functional>
#include "common.h"

class MQTT {
    public:
        MQTT(std::string &broker_);
        esp_err_t connect();
        esp_err_t publisher(const std::string &topic, 
                            const std::string &msg, 
                            int qos = 1,
                             bool retain = false);
        esp_err_t subscriber(const std::string &topic, 
                                const std::function<void (const std::string &msg)>& callback, 
                                int qos = 1);
        esp_err_t disconnect();
        ~MQTT() = default;
    private:
        esp_mqtt_client_handle_t client;
        std::string broker;
};

#endif