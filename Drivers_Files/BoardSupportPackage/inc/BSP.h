/*
 * BSP.h
 *
 *  Created on: Dec 30, 2016
 *      Author: Raz Aloni
 */

#ifndef BSP_H_
#define BSP_H_

/* Includes */

#include <BoardSupportPackage/inc/bme280_support.h>
#include <BoardSupportPackage/inc/bmi160_support.h>
#include <BoardSupportPackage/inc/BackChannelUart.h>
#include <BoardSupportPackage/inc/ClockSys.h>
#include <BoardSupportPackage/inc/Joystick.h>
#include <BoardSupportPackage/inc/leds.h>
#include <BoardSupportPackage/inc/LCD.h>
#include <BoardSupportPackage/inc/opt3001.h>
#include <BoardSupportPackage/inc/tmp007.h>
#include <stdint.h>


/********************************** Public Functions **************************************/

/* Initializes the entire board */
extern void BSP_InitBoard();

/********************************** Public Functions **************************************/

typedef enum device {
    BLUE = 0,
    GREEN = 1,
    RED = 2,
    PWM1 = 1,
    PWM2 = 2,
    ON = 3,
    OFF = 4
};

#endif /* BSP_H_ */
