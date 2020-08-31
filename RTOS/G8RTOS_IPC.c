

/*********************************************** Dependencies and Externs *************************************************************/
#include "G8RTOS_IPC.h"
#include "G8RTOS_Semaphores.h"

/*********************************************** Dependencies and Externs *************************************************************/


/*********************************************** Defines ******************************************************************************/


/*********************************************** Defines ******************************************************************************/


/*********************************************** Data Structures Used *****************************************************************/

typedef struct fifo_t
{
    int32_t buff[FIFO_SIZE];
    int32_t* head;
    int32_t* tail;
    uint32_t lostData;
    semaphore_t currSize;
    semaphore_t mutex;

} fifo_t;

/*********************************************** Data Structures Used *****************************************************************/


/*********************************************** Private Variables ********************************************************************/

static fifo_t FIFOS[MAX_FIFOS];

/*********************************************** Private Variables ********************************************************************/

/*********************************************** Private Functions ********************************************************************/

/*********************************************** Private Functions ********************************************************************/

/*********************************************** Public Variables *********************************************************************/

/*********************************************** Public Variables *********************************************************************/


/*********************************************** Public Functions *********************************************************************/

int G8RTOS_FIFO_Init(uint32_t index)
{
    if (index < MAX_FIFOS) {
        G8RTOS_InitSemaphore(&FIFOS[index].currSize, 0);
        G8RTOS_InitSemaphore(&FIFOS[index].mutex, 1);
        FIFOS[index].lostData = 0;
        FIFOS[index].head = &FIFOS[index].buff[0];
        FIFOS[index].tail = &FIFOS[index].buff[0];
    }
    else
    {
        return -1;
    }
    return 1;
}

uint32_t G8RTOS_Read_FIFO(int index)
{
    G8RTOS_WaitSemaphore(&FIFOS[index].currSize);
    G8RTOS_WaitSemaphore(&FIFOS[index].mutex);
    int32_t val = *FIFOS[index].head;
    if(FIFOS[index].head == &FIFOS[index].buff[FIFO_SIZE - 1])
    {
        FIFOS[index].head = &FIFOS[index].buff[0];
    }
    else
    {
        FIFOS[index].head++;
    }
    G8RTOS_SignalSemaphore(&FIFOS[index].mutex);
    return val;
}

uint32_t G8RTOS_Write_FIFO(int index, uint32_t value)
{
    G8RTOS_WaitSemaphore(&FIFOS[index].mutex);
    // check to see if the FIFO is full
    if(FIFOS[index].currSize == FIFO_SIZE)
    {
        FIFOS[index].lostData++;
    }
    *FIFOS[index].tail = value;
    if(FIFOS[index].tail == &FIFOS[index].buff[FIFO_SIZE - 1])
    {
        FIFOS[index].tail = &FIFOS[index].buff[0];
    }
    else
    {
        FIFOS[index].tail++;
    }
    G8RTOS_SignalSemaphore(&FIFOS[index].mutex);
    G8RTOS_SignalSemaphore(&FIFOS[index].currSize);
    return 1;
}
/*********************************************** Public Functions *********************************************************************/
