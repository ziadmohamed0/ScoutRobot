idf_component_register(
    SRCS "src/dc_motor.cpp" "src/TCRT5000.cpp" "src/ultrasonic.cpp" "src/MPU6050.cpp" "src/mqtt.cpp"
    INCLUDE_DIRS "inc"
    REQUIRES 
        driver
        freertos
        esp_timer
        esp_adc
        esp_common
        esp_event
        esp_netif
        esp_wifi
        nvs_flash
        mqtt
)
