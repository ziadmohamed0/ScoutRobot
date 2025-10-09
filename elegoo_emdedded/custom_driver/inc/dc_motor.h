#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include <vector>
#include "common.h"

enum class DC_MOTOR_DIRECTION : uint8_t {
    forward, backward, right, left
};

class dc_motor{
    public:
        /**
         * @brief Construct a new dc motor object (left forward motor, 
         *                                          left backward motor,
         *                                          right forward motor,
         *                                          right backward motor,)
         * 
         * @param pins 
         */
        dc_motor(std::vector<gpio_num_t> pins);
        void dc_move(DC_MOTOR_DIRECTION movement);
        ~dc_motor()= default;
    private:
        std::vector<gpio_num_t> pins;
        std::string direction;
};

#endif