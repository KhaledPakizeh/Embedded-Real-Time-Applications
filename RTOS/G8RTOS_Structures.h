/*
 * G8RTOS_Structure.h
 *
 *  Created on: Jan 12, 2017
 *      Author: Raz Aloni
 */

#ifndef G8RTOS_STRUCTURES_H_
#define G8RTOS_STRUCTURES_H_

#include "G8RTOS.h"
#define MAX_NAME_LENGTH 16

/*********************************************** Data Structure Definitions ***********************************************************/
typedef enum bool_t
{
    FALSE = 0,
    TRUE = 1
}bool_t;

typedef enum Pass_Parameters
{
    INDEX = 0,
    XPOS =1,
    YPOS =2

} Pass_Parameters;


typedef uint32_t threadId_t;
/*
 *  Thread Control Block:
 *      - Every thread has a Thread Control Block
 *      - The Thread Control Block holds information about the Thread Such as the Stack Pointer, Priority Level, and Blocked Status
 *      - For Lab 2 the TCB will only hold the Stack Pointer, next TCB and the previous TCB (for Round Robin Scheduling)
 */

typedef struct tcb_t
{
    uint32_t* sp;
    struct tcb_t* prev;
    struct tcb_t* next;
    semaphore_t* blocked;
    uint32_t sleepCount;
    // New goodies
    bool_t asleep;
    bool_t alive;
    uint8_t priority;
    char threadName[MAX_NAME_LENGTH];
    threadId_t ID;
}tcb_t;

typedef struct periodicEvent_t
{
    void (*Handler)(void);
    uint32_t period;
    uint32_t executeTime;
    struct periodicEvent_t* next;
    struct periodicEvent_t* prev;
}periodicEvent_t;

typedef enum sched_ErrCode_t
{
    NO_ERROR                   = 0,
    THREAD_LIMIT_REACHED       = -1,
    NO_THREADS_SCHEDULED       = -2,
    THREADS_INCORRECTLY_ALIVE  = -3,
    THREAD_DOES_NOT_EXIST      = -4,
    CANNOT_KILL_LAST_THREAD    = -5,
    IRQn_INVALID               = -6,
    HWI_PRIORITY_INVLAID       = -7
}sched_ErrCode_t;
/*********************************************** Data Structure Definitions ***********************************************************/

/*********************************************** Public Variables *********************************************************************/

tcb_t * CurrentlyRunningThread;

/*********************************************** Public Variables *********************************************************************/




#endif /* G8RTOS_STRUCTURES_H_ */
