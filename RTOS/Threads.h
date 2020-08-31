/*
 * Threads.h
 *
 *  Created on: Feb 6, 2020
 *      Author: Khaled Pakizeh
 */

#ifndef G8RTOS_THREADS_H_
#define G8RTOS_THREADS_H_

#include "G8RTOS_Semaphores.h"
#include "BSP.h"
#include "G8RTOS.h"
#include <time.h>
#include <stdlib.h>
#define MAX_BALLS 20
#define Radius 4
#define HIT_MISS 9

/*********************************************** Datatype Definitions *****************************************************************/


semaphore_t Accel_Sens;
semaphore_t Draw_on_lcd;
int16_t X_Val ;
int16_t Y_Val ;

/*********************************************** Datatype Definitions *****************************************************************/
// ball stuff
typedef struct ball_t
{
    int16_t xposition;
    int16_t yposition;
    threadId_t threadID;
    uint16_t Random_Speed;

    bool alive;
    uint16_t color;

} ball_t;

ball_t myballs[MAX_BALLS];

/*********************************************** Public Functions *********************************************************************/
void Screen_Touched(void);
void Debouncing_Thread(void);
void Ball_Thread(void);
void ReadAccel(void);
void idle(void);
/*********************************************** Public Functions *********************************************************************/

#endif /* G8RTOS_THREADS_H_ */
