/*
 * G8RTOS_Scheduler.h
 */

#ifndef G8RTOS_SCHEDULER_H_
#define G8RTOS_SCHEDULER_H_
#include "G8RTOS_Structures.h"
#include "driverlib.h"
#include "BSP.h"
#include "G8RTOS_CriticalSection.h"
#include <stdint.h>
#include "msp.h"
#include "msp432.h"
/*********************************************** Sizes and Limits *********************************************************************/
#define MAX_THREADS 20
#define MAX_EVENTS 6
#define MAX_THREAD_PRIORITY 255
#define STACKSIZE 512
#define OSINT_PRIORITY 7
#define MAX_NAME_LENGTH 16
/*********************************************** Sizes and Limits *********************************************************************/

/*********************************************** Public Variables *********************************************************************/

/* Holds the current time for the whole System */
extern uint32_t SystemTime;

/*********************************************** Public Variables *********************************************************************/
#define G8RTOS_CONTEXT_SWITCH()     SCB->ICSR |= 0x10000000;

// New Method for doubly linked list:
 tcb_t *Head_of_pointer;
 tcb_t *Tail_of_pointer;



/*********************************************** Public Functions *********************************************************************/

/*
 * Initializes variables and hardware for G8RTOS usage
 */
void G8RTOS_Init();

/*
 * Starts G8RTOS Scheduler
 * 	- Initializes Systick Timer
 * 	- Sets Context to first thread
 * Returns: Error Code for starting scheduler. This will only return if the scheduler fails
 */
int32_t G8RTOS_Launch();

/*
 * Adds threads to G8RTOS Scheduler
 * 	- Checks if there are stil available threads to insert to scheduler
 * 	- Initializes the thread control block for the provided thread
 * 	- Initializes the stack for the provided thread
 * 	- Sets up the next and previous tcb pointers in a round robin fashion
 * Param "threadToAdd": Void-Void Function to add as preemptable main thread
 * Returns: Error code for adding threads
 */
sched_ErrCode_t G8RTOS_AddThread(void (*threadToAdd)(void), uint8_t priority, char* threadID);

sched_ErrCode_t G8RTOS_AddPeriodicEvent(void (*eventToAdd)(void), uint32_t period, uint32_t offset);
/*
 * Sleeps the thread that calls this function
 * - Changes the value of the sleep property of the tcb
 * Param "sleep_ms": uint32_t amount of milliseconds to sleep
 */
void G8RTOS_OS_Sleep(uint32_t sleep_ms);

/*
 * Returns current running thread's ID
 */
threadId_t G8RTOS_Get_Thread_Id();
/*
 * KillThread
 * - changes threads "alive" to FALSE
 * - Param "threadID" the ID of the thread to kill
 */
sched_ErrCode_t G8RTOS_KillThread(threadId_t threadID);
/*
 * KillSelf
 * - changes calling threads "alive" to FALSE
 */
sched_ErrCode_t G8RTOS_KillSelf(void);
/*
 * Add APeriodic event
 *
 */
sched_ErrCode_t G8RTOS_ADDAPeriodicEvent(void(*AthreadToAdd)(void), uint8_t priority, IRQn_Type IRQn);


sched_ErrCode_t  G8RTOS_KillAllOtherThreads(void);
/*********************************************** Public Functions *********************************************************************/

#endif /* G8RTOS_SCHEDULER_H_ */
