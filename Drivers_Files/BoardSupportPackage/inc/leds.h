#ifndef LEDS_H_
#define LEDS_H_


void init_RGBLEDS();

void i2c_slave_write (uint32_t saddr, uint16_t sdata1, uint16_t sdata2);

//void LP3943_ColorSet(uint32_t unit, uint32_t PWM_SEL, double PWM_PERIOD, double PWM_DUTYCYCLE);

void LP3943_PWMSet(uint32_t unit, uint32_t PWM_SEL, uint32_t PWM_PERIOD, uint32_t PWM_DUTYCYCLE);

void LP3943_LEDSet(uint32_t unit, uint16_t LED_DATA, uint32_t LED_MODE);

#endif
