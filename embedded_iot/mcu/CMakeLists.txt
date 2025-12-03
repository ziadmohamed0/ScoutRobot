idf_component_register(
    SRCS
        "nvs/NVS.cpp"
        "wifi/WiFi.cpp"
        "mqtt/MQTT.cpp"
    INCLUDE_DIRS
        "nvs"
        "wifi"
        "mqtt"

    REQUIRES
        lib
)
