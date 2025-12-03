#ifndef TCRT5000_H_
#define TCRT5000_H_
#include "common.h"

class tcrt_sensor {
    public:
        tcrt_sensor(gpio_num_t d_pin);
        ~tcrt_sensor();
        bool readDigital();
        // float readAnaloge();
        
    private:
        gpio_num_t out_pin;
};

#endif