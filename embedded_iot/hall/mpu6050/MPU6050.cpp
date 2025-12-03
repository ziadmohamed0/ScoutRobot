#include "MPU6050.h"

MPU6050::MPU6050(gpio_num_t sda_, gpio_num_t scl_) : 
    bus_handle(nullptr),
    dev_handle(nullptr),
    sda(sda_),
    scl(scl_) {
    this->init();
}

MPU6050::~MPU6050() {
    if (this->dev_handle != nullptr) {
        i2c_master_bus_rm_device(this->dev_handle);
    }
    if (this->bus_handle != nullptr) {
        i2c_del_master_bus(this->bus_handle);
    }
}

esp_err_t MPU6050::init() {
    // Initialize I2C master bus
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = this->sda,
        .scl_io_num = this->scl,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false,
        },
    };
    
    esp_err_t ret = i2c_new_master_bus(&bus_config, &this->bus_handle);
    if (ret != ESP_OK) {
        return ret;
    }
    
    // Add MPU6050 device to the bus
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU6050_ADDR,
        .scl_speed_hz = 400000,
        .scl_wait_us = 0,
        .flags = {
            .disable_ack_check = false,
        },
    };
    
    ret = i2c_master_bus_add_device(this->bus_handle, &dev_config, &this->dev_handle);
    if (ret != ESP_OK) {
        return ret;
    }
    
    // Wake up MPU6050
    this->writeByte(0x6B, 0x00);
    vTaskDelay(pdMS_TO_TICKS(100));
    
    // Configure gyroscope
    this->writeByte(0x1B, 0x00);
    // Configure accelerometer
    this->writeByte(0x1C, 0x00);
    
    return ESP_OK;
}

esp_err_t MPU6050::writeByte(uint8_t reg, uint8_t data) {
    uint8_t write_buf[2] = {reg, data};
    return i2c_master_transmit(this->dev_handle, write_buf, 2, pdMS_TO_TICKS(1000));
}

esp_err_t MPU6050::readBytes(uint8_t reg, uint8_t* buffer, size_t length) {
    return i2c_master_transmit_receive(this->dev_handle, &reg, 1, buffer, length, pdMS_TO_TICKS(1000));
}

esp_err_t MPU6050::readAccel(float& ax, float& ay, float& az) {
    uint8_t data[6];
    if (readBytes(0x3B, data, 6) != ESP_OK)
        return ESP_FAIL;
    
    int16_t raw_ax = (data[0] << 8) | data[1];
    int16_t raw_ay = (data[2] << 8) | data[3];
    int16_t raw_az = (data[4] << 8) | data[5];
    
    ax = raw_ax / 16384.0f;
    ay = raw_ay / 16384.0f;
    az = raw_az / 16384.0f;
    
    return ESP_OK;
}

esp_err_t MPU6050::readGyro(float& gx, float& gy, float& gz) {
    uint8_t data[6];
    if (readBytes(0x43, data, 6) != ESP_OK)
        return ESP_FAIL;
    
    int16_t raw_gx = (data[0] << 8) | data[1];
    int16_t raw_gy = (data[2] << 8) | data[3];
    int16_t raw_gz = (data[4] << 8) | data[5];
    
    gx = raw_gx / 131.0f;
    gy = raw_gy / 131.0f;
    gz = raw_gz / 131.0f;
    
    return ESP_OK;
}

float MPU6050::readTemprature() {
    uint8_t data[2];
    if (readBytes(0x41, data, 2) != ESP_OK)
        return 0;
    
    int16_t raw_temp = (data[0] << 8) | data[1];
    return (raw_temp / 340.0f) + 36.53f;
}

void MPU6050::updateAngles(float dt) {
    float ax, ay, az, gx, gy, gz;
    readAccel(ax, ay, az);
    readGyro(gx, gy, gz);
    
    float roll_acc = atan2(ay, az) * 180 / M_PI;
    float pitch_acc = atan2(-ax, sqrt(ay*ay + az*az)) * 180 / M_PI;
    
    roll = alpha * (roll + gx * dt) + (1 - alpha) * roll_acc;
    pitch = alpha * (pitch + gy * dt) + (1 - alpha) * pitch_acc;
    yaw += gz * dt; 
}

float MPU6050::getRoll() {
    return this->roll;
}

float MPU6050::getPitch() {
    return this->pitch;
}

float MPU6050::getYaw() {
    return this->yaw;
}

float MPU6050::getAccx() {
    readAccel(this->accel_x, this->accel_y, this->accel_z);
    return this->accel_x;
}

float MPU6050::getAccy() {
    readAccel(this->accel_x, this->accel_y, this->accel_z);
    return this->accel_y;
}

float MPU6050::getAccz() {
    readAccel(this->accel_x, this->accel_y, this->accel_z);
    return this->accel_z;
}