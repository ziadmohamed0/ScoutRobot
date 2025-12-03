#include "TCRT5000.h"

tcrt_sensor::tcrt_sensor(gpio_num_t d_pin) : 
    out_pin(d_pin){
    
    // Configure digital pin
    gpio_set_direction(this->out_pin, GPIO_MODE_INPUT);
    
    // Configure ADC oneshot
    // adc_oneshot_unit_init_cfg_t init_config = {
    //     .unit_id = this->adc_unit,
    //     .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
    //     .ulp_mode = ADC_ULP_MODE_DISABLE,
    // };
    // adc_oneshot_new_unit(&init_config, &this->adc_handle);
    
    // // Configure ADC channel
    // adc_oneshot_chan_cfg_t config = {
    //     .atten = ADC_ATTEN_DB_12,
    //     .bitwidth = ADC_BITWIDTH_12,
    // };
    // adc_oneshot_config_channel(this->adc_handle, this->adc_channel, &config);
}

tcrt_sensor::~tcrt_sensor() {
    // if (this->adc_handle != nullptr) {
    //     adc_oneshot_del_unit(this->adc_handle);
    // }
}

bool tcrt_sensor::readDigital() {
    return gpio_get_level(this->out_pin);
}

// float tcrt_sensor::readAnaloge() {
//     int raw_value = 0;
//     adc_oneshot_read(this->adc_handle, this->adc_channel, &raw_value);
//     return raw_value;
// }