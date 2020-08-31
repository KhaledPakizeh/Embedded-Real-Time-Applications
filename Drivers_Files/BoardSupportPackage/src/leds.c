#include "msp.h"
#include "leds.h"
#include <BSP.h>
#include <driverlib.h>

void init_RGBLEDS () {
    UCB2CTLW0 = UCSWRST;
    UCB2CTLW0 |= UCSSEL_2 | UCSYNC | UCMST | UCMODE_3;
    UCB2BRW = 30;
    P3SEL0 |= 0xC0;
    P3SEL1 &= ~0xC0;
    UCB2CTLW0 &= ~UCSWRST;
/*    LP3943_LEDSet(RED, 0xFFFF, OFF);
    LP3943_LEDSet(GREEN, 0xFFFF, OFF);
    LP3943_LEDSet(BLUE, 0xFFFF, OFF);
*/
}

void i2c_slave_write (uint32_t saddr, uint16_t sdata1, uint16_t sdata2) {
    UCB2I2CSA = saddr;
    UCB2CTLW0 |= UCTR;
    UCB2CTLW0 |= UCTXSTT;
    while(UCB2CTLW0 & UCTXSTT);
    UCB2TXBUF = sdata1;
    while(!(UCB2IFG & UCTXIFG0));
    UCB2TXBUF = sdata2;
    while(!(UCB2IFG & UCTXIFG0));
    UCB2CTLW0 |= UCTXSTP;
    while(UCB2CTLW0 & UCTXSTP);
}


void LP3943_PWMSet(uint32_t unit, uint32_t PWM_SEL, uint32_t PWM_PERIOD, uint32_t PWM_DUTYCYCLE) {
    if (PWM_SEL == 1) {
        i2c_slave_write(0x60 + unit, 0x2, PWM_PERIOD);
        i2c_slave_write(0x60 + unit, 0x3, PWM_DUTYCYCLE);
    }
    else if (PWM_SEL == 2) {
        i2c_slave_write(0x60 + unit, 0x4, PWM_PERIOD);
        i2c_slave_write(0x60 + unit, 0x5, PWM_DUTYCYCLE);
    }
}


void LP3943_LEDSet(uint32_t unit, uint16_t LED_DATA, uint32_t LED_MODE) {
    uint8_t ls0_val = 0, ls1_val = 0, ls2_val = 0, ls3_val = 0;

    if (LED_MODE == 1) {

        if ((LED_DATA & 0x1) != 0) {
            ls0_val |= 0x2;
        }
        if ((LED_DATA & 0x2) != 0) {
            ls0_val |= 0x8;
        }
        if ((LED_DATA & 0x4) != 0) {
            ls0_val |= 0x20;
        }
        if ((LED_DATA & 0x8) != 0) {
            ls0_val |= 0x80;
        }
        if ((LED_DATA & 0x10) != 0) {
            ls1_val |= 0x2;
        }
        if ((LED_DATA & 0x20) != 0) {
            ls1_val |= 0x8;
        }
        if ((LED_DATA & 0x40) != 0) {
            ls1_val |= 0x20;
        }
        if ((LED_DATA & 0x80) != 0) {
            ls1_val |= 0x80;
        }
        if ((LED_DATA & 0x100) != 0) {
            ls2_val |= 0x2;
        }
        if ((LED_DATA & 0x200) != 0) {
            ls2_val |= 0x8;
        }
        if ((LED_DATA & 0x400) != 0) {
            ls2_val |= 0x20;
        }
        if ((LED_DATA & 0x800) != 0) {
            ls2_val |= 0x80;
        }
        if ((LED_DATA & 0x1000) != 0) {
            ls3_val |= 0x2;
        }
        if ((LED_DATA & 0x2000) != 0) {
            ls3_val |= 0x8;
        }
        if ((LED_DATA & 0x4000) != 0) {
            ls3_val |= 0x20;
        }
        if ((LED_DATA & 0x8000) != 0) {
            ls3_val |= 0x80;
        }
    }

    else if (LED_MODE == 2) {

        if ((LED_DATA & 0x1) != 0) {
            ls0_val |= 0x3;
        }
        if ((LED_DATA & 0x2) != 0) {
            ls0_val |= 0xC;
        }
        if ((LED_DATA & 0x4) != 0) {
            ls0_val |= 0x30;
        }
        if ((LED_DATA & 0x8) != 0) {
            ls0_val |= 0xC0;
        }
        if ((LED_DATA & 0x10) != 0) {
            ls1_val |= 0x3;
        }
        if ((LED_DATA & 0x20) != 0) {
            ls1_val |= 0xC;
        }
        if ((LED_DATA & 0x40) != 0) {
            ls1_val |= 0x30;
        }
        if ((LED_DATA & 0x80) != 0) {
            ls1_val |= 0xC0;
        }
        if ((LED_DATA & 0x100) != 0) {
            ls2_val |= 0x3;
        }
        if ((LED_DATA & 0x200) != 0) {
            ls2_val |= 0xC;
        }
        if ((LED_DATA & 0x400) != 0) {
            ls2_val |= 0x30;
        }
        if ((LED_DATA & 0x800) != 0) {
            ls2_val |= 0xC0;
        }
        if ((LED_DATA & 0x1000) != 0) {
            ls3_val |= 0x3;
        }
        if ((LED_DATA & 0x2000) != 0) {
            ls3_val |= 0xC;
        }
        if ((LED_DATA & 0x4000) != 0) {
            ls3_val |= 0x30;
        }
        if ((LED_DATA & 0x8000) != 0) {
            ls3_val |= 0xC0;
        }
    }


    else if (LED_MODE == 3) {

        if ((LED_DATA & 0x1) != 0) {
            ls0_val |= 0x1;
        }
        if ((LED_DATA & 0x2) != 0) {
            ls0_val |= 0x4;
        }
        if ((LED_DATA & 0x4) != 0) {
            ls0_val |= 0x10;
        }
        if ((LED_DATA & 0x8) != 0) {
            ls0_val |= 0x40;
        }
        if ((LED_DATA & 0x10) != 0) {
            ls1_val |= 0x1;
        }
        if ((LED_DATA & 0x20) != 0) {
            ls1_val |= 0x4;
        }
        if ((LED_DATA & 0x40) != 0) {
            ls1_val |= 0x10;
        }
        if ((LED_DATA & 0x80) != 0) {
            ls1_val |= 0x40;
        }
        if ((LED_DATA & 0x100) != 0) {
            ls2_val |= 0x1;
        }
        if ((LED_DATA & 0x200) != 0) {
            ls2_val |= 0x4;
        }
        if ((LED_DATA & 0x400) != 0) {
            ls2_val |= 0x10;
        }
        if ((LED_DATA & 0x800) != 0) {
            ls2_val |= 0x40;
        }
        if ((LED_DATA & 0x1000) != 0) {
            ls3_val |= 0x1;
        }
        if ((LED_DATA & 0x2000) != 0) {
            ls3_val |= 0x4;
        }
        if ((LED_DATA & 0x4000) != 0) {
            ls3_val |= 0x10;
        }
        if ((LED_DATA & 0x8000) != 0) {
            ls3_val |= 0x40;
        }
    }

    i2c_slave_write(0x60 + unit, 0x6, ls0_val);
    i2c_slave_write(0x60 + unit, 0x7, ls1_val);
    i2c_slave_write(0x60 + unit, 0x8, ls2_val);
    i2c_slave_write(0x60 + unit, 0x9, ls3_val);
}
