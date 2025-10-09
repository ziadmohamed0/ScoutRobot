#include "dc_motor.h"

dc_motor::dc_motor(std::vector<gpio_num_t> p) : pins(p) {
    for(auto &motorPins : this->pins) {
        gpio_set_direction(motorPins, GPIO_MODE_OUTPUT);
    }
}

void dc_motor::dc_move(DC_MOTOR_DIRECTION movement) {
    switch(movement) {
        case DC_MOTOR_DIRECTION::forward:
            for(int index = 0; index < this->pins.size(); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
            }
            break;
        case DC_MOTOR_DIRECTION::backward:
            for(int index = 0; index < this->pins.size(); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
            }
            break;
        case DC_MOTOR_DIRECTION::right:
            for(int index = (this->pins.size() / 2); index < this->pins.size(); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
            }
            for(int index = 0; index < (this->pins.size() / 2); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
            }
            break;
        case DC_MOTOR_DIRECTION::left:
            for(int index = 0; index < (this->pins.size() / 2); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
            }
            for(int index = (this->pins.size() / 2); index < this->pins.size(); index++) {
                if(index%2 == false) {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::LOW));
                }
                else {
                    gpio_set_level(this->pins[index], static_cast<uint32_t>(status::HIGH));
                }
            }
            break;
    }
}
