/*
 * game.h
 *
 *  Created on: Aug 28, 2020
 *      Author: Khaled
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "G8RTOS.h"

#define water_highet 13
#define water_width 17

#define Standongrass_highet 8
#define Standongrass_width 22
#define Standontree_highet 23
#define Standontree_width 31
#define Log_highet 10
#define Log_width 41
#define Climbingtree_highet 70
#define Climbingtree_width 7

#define Monkey_still_highet 18
#define Monkey_still_width 27

#define Monkey_walk1_h 18
#define Monkey_walk1_w 27

#define Monkey_walk2_h 18
#define Monkey_walk2_w 27

#define Monkey_Climb1_h 17
#define Monkey_Clim1_w 20


#define Monkey_Climb2_h 20
#define Monkey_Clim2_w 21

#define Mario_Attack_Mode_h 16
#define Mario_Attack_Mode_w 17

#define Big_Kong_H 32 
#define Big_Kong_W 51

#define Beast1_H 9 
#define Beast1_W 16

#define Beast2_H 11 
#define Beast2_W 17




semaphore_t LCD_USAGE;


 
typedef struct
{

    uint16_t Climbingtree[490];
    uint16_t log[410];
    uint16_t water[221];
    uint16_t standontgrass[176];
    uint16_t standontree[713];
    uint16_t Mario [272];
    uint16_t Big_Kong [1632];
    uint16_t Beast1 [144];
    uint16_t Beast2 [187];

} MAP;

typedef struct {
int16_t x,y;

} PointLoc;

typedef struct {

    uint16_t sitting[486];
    uint16_t Walking1[486];
    uint16_t Walking2[486];

    uint16_t climbing1 [340];
    uint16_t climbing2 [420];

   PointLoc Center; 
   PointLoc Old_Center;
   PointLoc Offset;
   int Case;
   int Old_Case;
   int Carry_Case_Over;
   




} Monkey;

typedef enum {
Stand_Still =0,
Walk_f1 =1,
Walk_f2 =2,

Climb_f1 =3,
Climb_f2 =4

} Mokeny_Motion_Cases;



MAP *Kong_map_ptr;
Monkey *Monkey_ptr;


/****************************************************** Helper Functions **************************************/
void Draw_map();
void Update_Player();
void Read_stcik();

/******************************************************** Game Threads ****************************************/

void IDLE();
void Start_game();
void Draw_Objects();

#endif /* GAME_GAME_H_ */
