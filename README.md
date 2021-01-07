# Embedded-Real-Time-Applications:
This project served as a final project for Microprocessors applications II where student where paried and tasked with coming up with a final project for the class. The games use an Real time operating system (RTOS) created throughout the course. Lunchpad: TI MSP432 (ARM Cortex M4) Backpacks: TI CC3100 Wi-Fi® Network Processor

## Hardware used: 

- Devlopement board used for this project is the [MSP432](https://www.ti.com/product/MSP432P401R?utm_source=google&utm_medium=cpc&utm_campaign=epd-con-null-prodfolderdynamic-cpc-pf-google-wwe&utm_content=prodfolddynamic&ds_k=DYNAMIC+SEARCH+ADS&DCM=yes&gclid=CjwKCAjwnK36BRBVEiwAsMT8WNJew8yfEwyencFXfZz1lk2-7xudpZduXpiaQ3Wu68337mU4iZ0bFhoCgBIQAvD_BwE&gclsrc=aw.ds).
### Hardware limitations:
SRAM 64 KB
Due to the memory limitations we were only able to create two games that used the SRAM along with our drivers.
### Other backpacks: 
 - [CCS3100 BOOSTER PACK CC3100 WI-FI & IOT](https://www.digikey.com/product-detail/en/texas-instruments/CC3100BOOST/296-37769-ND/4862810?utm_adgroup=RF%2FIF%20and%20RFID&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Texas%20Instruments_0296_Co-op&utm_term=&utm_content=RF%2FIF%20and%20RFID&gclid=CjwKCAjw8df2BRA3EiwAvfZWaJutkkvgnPuYSjb0I8DprFYE4M8eggaCiC-Tff1q4PmoknfxObZhlxoCDgAQAvD_BwE) was used in this project to allow the development boards to commuincate via UDP or TCP. 
![](Pics/Back_Packs.jpeg)

- Custom PCB designed by UF [HKN](https://hkn.ece.ufl.edu/).

![](Pics/Development_Board.jpeg)

## Real time operating system (RTOS)
### In this course we gradually created our own RTOS which consists of the following: 
- Scheduler
  - Services threads based on priority
  -  Able to service periodic and aperiodic threads 
- Interprocess commuincations (IPC) 
  - Used FIFOs to have threads exchange data sufficiently
 Link: [RTOS](https://github.com/Kpakizeh/Embedded-Real-Time-Applications/tree/master/RTOS)
- Semaphores: 
  - Used semaphores as a (mutex) locks and for suffiecent CPU time usage (efficiency).
 
## Games
### **Donkey Kong Jr (Developed by Khaled) - Solo play** 
![](Pics/Donkey_Kong.jpeg)
The point of this game is for Jr to resuce his father from mario (by touching mario) with out getting hit by the flying dragons. 

### **Pong (Developed by Sobhi and Khaled) - Multi-player**
![](Pics/Pong_Wi-Fi.jpeg)


This games uses the [CCS3100 BOOSTER PACK CC3100 WI-FI & IOT](https://www.digikey.com/product-detail/en/texas-instruments/CC3100BOOST/296-37769-ND/4862810?utm_adgroup=RF%2FIF%20and%20RFID&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Texas%20Instruments_0296_Co-op&utm_term=&utm_content=RF%2FIF%20and%20RFID&gclid=CjwKCAjw8df2BRA3EiwAvfZWaJutkkvgnPuYSjb0I8DprFYE4M8eggaCiC-Tff1q4PmoknfxObZhlxoCDgAQAvD_BwE) to be played over Wi-Fi. The point of this game is to score 15 points against the other player to dominate the round. 
