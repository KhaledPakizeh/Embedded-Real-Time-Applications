/*
 * G8RTOS_Semaphores.c
 */

/*********************************************** Dependencies and Externs *************************************************************/

#include <stdint.h>
#include "msp.h"
#include "G8RTOS.h"
#include "G8RTOS_Semaphores.h"
#include "G8RTOS_Structures.h"
#include "G8RTOS_CriticalSection.h"

/*********************************************** Dependencies and Externs *************************************************************/


/*********************************************** Public Functions *********************************************************************/

/*
 * Initializes a semaphore to a given value
 * Param "s": Pointer to semaphore
 * Param "value": Value to initialize semaphore to
 * THIS IS A CRITICAL SECTION
 */
void G8RTOS_InitSemaphore(semaphore_t *s, int32_t value)
{
	uint8_t status = StartCriticalSection();
	*s = value;
	EndCriticalSection(status);
}

/*
 * Waits for a semaphore to be available (value greater than 0)
 * 	- Decrements semaphore when available
 * 	- Spinlocks to wait for semaphore
 * Param "s": Pointer to semaphore to wait on
 * THIS IS A CRITICAL SECTION
 */
void G8RTOS_WaitSemaphore(semaphore_t *s)
{
    uint8_t status = StartCriticalSection();
    (*s)--;
    // if blocked
    if(*s < 0)
    {
        // point the tcb.blocked to the semaphore
        CurrentlyRunningThread->blocked = s;
        // enable interrupts
        EndCriticalSection(status);
        // Yield the thread
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
	EndCriticalSection(status);
}

/*
 * Signals the completion of the usage of a semaphore
 * 	- Increments the semaphore value by 1
 * Param "s": Pointer to semaphore to be signalled
 * THIS IS A CRITICAL SECTION
 */
void G8RTOS_SignalSemaphore(semaphore_t *s)
{
    uint8_t status = StartCriticalSection();
    // release the semaphore
    (*s)++;
    // if there are threads still blocked
    if(*s <= 0)
    {
        tcb_t *nextThread = CurrentlyRunningThread->next;
        // search linked list for the blocked thread
        while(nextThread->blocked != s)
        {
            nextThread = nextThread->next;
        }
        nextThread->blocked = 0;
    }
	EndCriticalSection(status);
}

/*********************************************** Public Functions *********************************************************************/


