    #include "mqtt.h"

    MQTT::MQTT(std::string &broker_) :
                broker(broker_) {}

    esp_err_t MQTT::connect() {
        /* set variable for mqtt configurations */
        esp_mqtt_client_config_t cfg = {};
        
        /* set ip of broker without tcp */
        // cfg.broker.address.uri = "mqtt://192.168.100.25";

        /* set ip of broker with tcp */
        cfg.broker.address.hostname = "192.168.100.25";
        cfg.broker.address.port = 1883;
        cfg.broker.address.transport = MQTT_TRANSPORT_OVER_TCP;

        /* number of secound between ping */
        cfg.session.keepalive = 60;

        /* automatic connection */
        cfg.network.disable_auto_reconnect = false;

        /* create a client mqtt handle if falid return nullptr */
        this->client = esp_mqtt_client_init(&cfg);
        if(!this->client) {
            return ESP_FAIL;
        }

        /* start to connection */
        esp_err_t ret = esp_mqtt_client_start(this->client);
        if(ret != ESP_OK) {
            return ESP_FAIL;
        }

        return ESP_OK;
    }

    esp_err_t MQTT::publisher(const std::string &topic, 
                        const std::string &msg, 
                        int qos,
                        bool retain) {
        /* check if connection is avilable */
        if(!this->client) {
            return ESP_FAIL;
        }

        
    }

    esp_err_t MQTT::subscriber(const std::string &topic, 
                            const std::function<void (const std::string &msg)>& callback, 
                            int qos) {
        return ESP_OK;

    }

    esp_err_t MQTT::disconnect() {
        return ESP_OK;

    }