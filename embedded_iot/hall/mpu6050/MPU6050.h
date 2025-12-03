#ifndef MPU6050_H_
#define MPU6050_H_
#include "common.h"
#include <cmath>

class MPU6050 {
    public:
        MPU6050(gpio_num_t sda_, gpio_num_t scl_);
        ~MPU6050();
        esp_err_t readAccel(float& ax, float& ay, float& az);
        esp_err_t readGyro(float& gx, float& gy, float& gz);
        float readTemprature();
        void updateAngles(float dt); 
        float getRoll();
        float getPitch();
        float getYaw();
        float getAccx();
        float getAccy();
        float getAccz();
        
    private:
        esp_err_t writeByte(uint8_t reg, uint8_t data);
        esp_err_t readBytes(uint8_t reg, uint8_t* buffer, size_t length);
        esp_err_t init();
        
        i2c_master_bus_handle_t bus_handle;
        i2c_master_dev_handle_t dev_handle;
        gpio_num_t sda;
        gpio_num_t scl;
        
        float roll = 0;
        float pitch = 0;
        float yaw = 0;
        float alpha = 0.98;
        float accel_x = 0;
        float accel_y = 0;
        float accel_z = 0; 
        
        static constexpr uint8_t MPU6050_ADDR = 0x68;
};

#endif