

#ifndef G8RTOS_G8RTOS_IPC_H_
#define G8RTOS_G8RTOS_IPC_H_
#include <stdint.h>


/*********************************************** Sizes and Limits *********************************************************************/
#define MAX_FIFOS 4
#define FIFO_SIZE 16
/*********************************************** Sizes and Limits *********************************************************************/

/*********************************************** Public Variables *********************************************************************/

/*********************************************** Public Variables *********************************************************************/


/*********************************************** Public Functions *********************************************************************/
/*
 * Initializes a FIFO
 * @param index the FIFO you want to initalize
 * @returnVal returns weather the fifow was initialized or not
 */
int G8RTOS_FIFO_Init(uint32_t index);

/*
 * Reads from a given FIFO
 * @param index the fifo you want to initalize
 * @returnVal returns weather the fifow was initialized or not
 */
uint32_t G8RTOS_Read_FIFO(int index);

/*
 * Writes to a given FIFO
 * @param index the FIFO you want to write to
 * @param vlaue the value to be written to the FIFO
 * @returnVal returns weather the FIFO was written to or not
 */
uint32_t G8RTOS_Write_FIFO(int index, uint32_t value);
/*********************************************** Public Functions *********************************************************************/



#endif /* G8RTOS_G8RTOS_IPC_H_ */
