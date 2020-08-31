/*
 * Game.c
 *
 *  Created on: Apr 13, 2020
 *      Author: Khaled
 */

#include "Game.h"
#include "msp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "G8RTOS.h"
#include "cc3100_usage.h"

#include "time.h"
#include "math.h"
GameState_t gameState;

SpecificPlayerInfo_t ClientSpecificInfo;
uint8_t Just_Started =1;



/***********************************************************************PUBLIC_ FUNCI and Threads  *********************************************************/
void InitButtons() {
//B0
    P4->DIR &= ~BIT4;
     P4->IFG &= ~BIT4;
     P4->IE |= BIT4;
     P4->IES|= BIT4;
     P4->REN |= BIT4;
     P4->OUT |= BIT4;
//B3
    P5->DIR &= ~BIT5;
    P5->IFG &= ~BIT5;
    P5->IE |= BIT5;
    P5->IES|= BIT5;
    P5->REN |= BIT5;
    P5->OUT |= BIT5;


}



void InitBoardState(){

    G8RTOS_WaitSemaphore(&LCD_USAGE);
    LCD_Clear(LCD_BLACK);
    PrintOverallScores(false);

        // White Boundries
       LCD_DrawRectangle(ARENA_MIN_X-1, ARENA_MIN_X, ARENA_MIN_Y, ARENA_MAX_Y, LCD_WHITE);
       LCD_DrawRectangle(ARENA_MAX_X, ARENA_MAX_X+1, ARENA_MIN_Y, ARENA_MAX_Y, LCD_WHITE);


       // Put BLUE Paddle at the top
       LCD_DrawRectangle(Left_Edge_Of_Paddle, Right_Edge_Of_Paddle,
                         TOP_OF_TOP_PADDEL, BOTTOm_OF_TOP_PADDEL,
                         PLAYER_BLUE);


     // Put RED Paddle at the Bottom
       LCD_DrawRectangle(Left_Edge_Of_Paddle, Right_Edge_Of_Paddle,
                         TOP_OF_BOTTOM_PADDEL, BOTTOm_OF_BOTTOm_PADDEL,
                               PLAYER_RED);
       G8RTOS_SignalSemaphore(&LCD_USAGE);


    }




void UpdatePlayerOnScreen(PrevPlayer_t * prevPlayerIn, GeneralPlayerInfo_t * outPlayer)
{



    if ( prevPlayerIn->Center != outPlayer->currentCenter )
    {


        int16_t Displacement_of_paddle = outPlayer->currentCenter - prevPlayerIn->Center;
        int16_t Displacement_of_paddle_ABS = abs(Displacement_of_paddle);



        int16_t Paddle_Left_Edge_Prev = prevPlayerIn->Center - PADDLE_LEN_D2;
        int16_t Paddle_Right_Edge_Prev = prevPlayerIn->Center + PADDLE_LEN_D2;


        int16_t Paddle_Left_Edge_Next = outPlayer->currentCenter - PADDLE_LEN_D2;
        int16_t Paddle_Right_Edge_Next = outPlayer->currentCenter + PADDLE_LEN_D2;


        G8RTOS_WaitSemaphore(&LCD_USAGE);
        if ( Displacement_of_paddle > 0 )
        {


            if(outPlayer->position == BOTTOM){
                            LCD_DrawRectangle(Paddle_Left_Edge_Prev, Paddle_Left_Edge_Prev + Displacement_of_paddle_ABS,
                                                      TOP_OF_BOTTOM_PADDEL, BOTTOm_OF_BOTTOm_PADDEL, BACK_COLOR);
                            LCD_DrawRectangle(Paddle_Right_Edge_Next-Displacement_of_paddle_ABS , Paddle_Right_Edge_Next ,
                                                                     TOP_OF_BOTTOM_PADDEL, BOTTOm_OF_BOTTOm_PADDEL, outPlayer->color);


                        }

            else if(outPlayer->position == TOP){
                                        LCD_DrawRectangle(Paddle_Left_Edge_Prev, Paddle_Left_Edge_Prev + Displacement_of_paddle_ABS,
                                                          TOP_OF_TOP_PADDEL, BOTTOm_OF_TOP_PADDEL, BACK_COLOR);
                                        LCD_DrawRectangle(Paddle_Right_Edge_Next-Displacement_of_paddle_ABS , Paddle_Right_Edge_Next ,
                                                          TOP_OF_TOP_PADDEL, BOTTOm_OF_TOP_PADDEL, outPlayer->color);


                                    }



        }




        else if ( Displacement_of_paddle < 0 )
        {

            if(outPlayer->position == BOTTOM){

                LCD_DrawRectangle(Paddle_Right_Edge_Prev-Displacement_of_paddle_ABS, Paddle_Right_Edge_Prev,
                                          TOP_OF_BOTTOM_PADDEL, BOTTOm_OF_BOTTOm_PADDEL, BACK_COLOR);
                LCD_DrawRectangle(Paddle_Left_Edge_Next, Paddle_Left_Edge_Next + Displacement_of_paddle_ABS ,
                                                         TOP_OF_BOTTOM_PADDEL, BOTTOm_OF_BOTTOm_PADDEL, outPlayer->color);

            }

            else if(outPlayer->position == TOP){

                            LCD_DrawRectangle(Paddle_Right_Edge_Prev-Displacement_of_paddle_ABS, Paddle_Right_Edge_Prev,
                                              TOP_OF_TOP_PADDEL, BOTTOm_OF_TOP_PADDEL, BACK_COLOR);
                            LCD_DrawRectangle(Paddle_Left_Edge_Next, Paddle_Left_Edge_Next + Displacement_of_paddle_ABS ,
                                              TOP_OF_TOP_PADDEL, BOTTOm_OF_TOP_PADDEL, outPlayer->color);

                        }



        }


        prevPlayerIn->Center = outPlayer->currentCenter;

       }
    G8RTOS_SignalSemaphore(&LCD_USAGE);
    }


void UpdateBallOnScreen(PrevBall_t * previousBall, Ball_t * currentBall, uint16_t outColor, int i){
    G8RTOS_WaitSemaphore(&LCD_USAGE);
    LCD_DrawRectangle(previousBall->CenterX - 2, previousBall->CenterX + 2, previousBall->CenterY - 2, previousBall->CenterY + 2, LCD_BLACK);
    LCD_DrawRectangle(previousBall->CenterX - 2, previousBall->CenterX + 2, previousBall->CenterY - 2, previousBall->CenterY + 2, LCD_BLACK);
    previousBall->CenterX = currentBall->currentCenterX;
    previousBall->CenterY = currentBall->currentCenterY;
    LCD_DrawRectangle(currentBall->currentCenterX - 2, currentBall->currentCenterX  + 2,currentBall->currentCenterY - 2, currentBall->currentCenterY + 2,outColor);
    G8RTOS_SignalSemaphore(&LCD_USAGE);

}



void IdleThread(){

    while(1);
}





void DrawObjects(){

    PrevPlayer_t Prev_Loc_Of_Players[MAX_NUM_OF_PLAYERS];
    PrevBall_t BALL[8];


    // At the start we r at the middle
    Prev_Loc_Of_Players[BOTTOM].Center = PADDLE_X_CENTER;
    Prev_Loc_Of_Players[TOP].Center = PADDLE_X_CENTER;




    while(1){

        for (int i = 0; i < MAX_NUM_OF_BALLS; i++ ){

            if(gameState.balls[i].alive && (!gameState.balls[i].On_Screen)) {
                UpdateBallOnScreen(&BALL[i], &gameState.balls[i], LCD_WHITE, i);

                gameState.balls[i].On_Screen =true;


            }

            else if(gameState.balls[i].alive) {
                UpdateBallOnScreen(&BALL[i], &gameState.balls[i], gameState.balls[i].color, i);
            }

            else {
                UpdateBallOnScreen(&BALL[i], &gameState.balls[i], LCD_BLACK, i);

                gameState.balls[i].color = LCD_WHITE;


            }

        }
       UpdatePlayerOnScreen(&Prev_Loc_Of_Players[BOTTOM], &gameState.players[BOTTOM]);
       UpdatePlayerOnScreen(&Prev_Loc_Of_Players[TOP], &gameState.players[TOP]);
       G8RTOS_OS_Sleep(25);
    }
}










/*************************************************************************Host Shit *********************************************************************************/

void CreateGame() {
    //new game
    if(!restartFlag) {
        LCD_Clear(LCD_BLACK);
        LCD_Text(10,80, "Waiting for Client to join", LCD_RED);
        gameState.players[TOP].color = PLAYER_BLUE;
        gameState.players[TOP].currentCenter =  MAX_SCREEN_X / 2;
        gameState.players[TOP].position = TOP;
        gameState.players[BOTTOM].color = PLAYER_RED;
        gameState.players[BOTTOM].currentCenter =  MAX_SCREEN_X / 2;
        gameState.players[BOTTOM].position = BOTTOM;
        gameState.restartGame = false;
        ClientSpecificInfo.ackEndofGame = false;
        gameState.numberOfBalls =0;
        initCC3100(Host);
        while( ReceiveData((_u8*)&gameState.player, sizeof(gameState.player)) == NOTHING_RECEIVED );
        gameState.player.joined = true;
        SendData((_u8*)&gameState, gameState.player.IP_address, sizeof(gameState) );
        while(gameState.player.acknowledge == false){
            ReceiveData((uint8_t*)&gameState.player, sizeof(gameState.player));
        }
        gameState.overallScores[TOP] = 0;
        gameState.overallScores[BOTTOM] = 0;
        gameState.LEDScores[TOP] = 0;
        gameState.LEDScores[BOTTOM] = 0;
        LP3943_LEDSet(RED, 0xFFFF, OFF);
        LP3943_LEDSet(BLUE, 0xFFFF, OFF);
        InitBoardState();
        for(int i = 0; i < MAX_NUM_OF_BALLS; i++) {
            gameState.balls[i].color = LCD_WHITE;
            gameState.balls[i].alive = false;
            gameState.balls[i].On_Screen = false;
            gameState.balls[i].currentCenterX = MAX_SCREEN_X/2;
            gameState.balls[i].currentCenterY = MAX_SCREEN_Y/2;
        }
        G8RTOS_AddThread( &IdleThread, 255, "My_Idle");
        G8RTOS_AddThread(&ReadJoystickHost, 20,"Read_Host_Stick" );
        G8RTOS_AddThread(&DrawObjects, 10, "Draw_Obj" );
        G8RTOS_AddThread(&MoveLEDs, 25, "MoveLEDs" );
        G8RTOS_AddThread(&SendDataToClient, 15, "Send_Data");
        G8RTOS_AddThread(&ReceiveDataFromClient, 15, "Get_Data_From_cLIENT");
        G8RTOS_AddThread(&GenerateBall, 20, "Generate_Ball" );
        gameState.numberOfBalls =0;
        G8RTOS_KillSelf();
    }
    //restart game
    else {
        gameState.LEDScores[TOP] = 0;
        gameState.LEDScores[BOTTOM] = 0;
        LP3943_LEDSet(RED, 0xFFFF, OFF);
        LP3943_LEDSet(BLUE, 0xFFFF, OFF);
        gameState.restartGame = true;
      //  while( ReceiveData((_u8*)&gameState.player, sizeof(gameState.player)) < 0 );
        SendData((uint8_t*)&gameState,gameState.player.IP_address, sizeof(gameState));
        gameState.restartGame = false;
    //    ClientSpecificInfo.ackEndofGame = false;
        gameState.numberOfBalls = 0;
        LCD_Clear(LCD_BLACK);
        gameState.players[TOP].color = PLAYER_BLUE;
        gameState.players[TOP].currentCenter =  MAX_SCREEN_X / 2;
        gameState.players[TOP].position = TOP;
        gameState.players[BOTTOM].color = PLAYER_RED;
        gameState.players[BOTTOM].currentCenter =  MAX_SCREEN_X / 2;
        gameState.players[BOTTOM].position = BOTTOM;
        for(int i = 0; i < MAX_NUM_OF_BALLS; i++) {
            gameState.balls[i].color = LCD_WHITE;
            gameState.balls[i].alive = false;
            gameState.balls[i].On_Screen = false;
            gameState.balls[i].currentCenterX = MAX_SCREEN_X/2;
            gameState.balls[i].currentCenterY = MAX_SCREEN_Y/2;
        }
        InitBoardState();
        G8RTOS_AddThread(&IdleThread, 255, "My_Idle");
        G8RTOS_AddThread(&ReadJoystickHost, 20,"Read_Host_Stick" );
        G8RTOS_AddThread(&DrawObjects, 10, "Draw_Obj" );
        G8RTOS_AddThread(&MoveLEDs, 25, "MoveLEDs" );
        G8RTOS_AddThread(&SendDataToClient, 15, "Send_Data");
        G8RTOS_AddThread(&ReceiveDataFromClient, 15, "Get_Data_From_cLIENT");
        G8RTOS_AddThread(&GenerateBall, 20, "Generate_Ball" );
        G8RTOS_KillSelf();
    }
}





void GenerateBall(){

    while(1){

     if(gameState.numberOfBalls < MAX_NUM_OF_BALLS){
         G8RTOS_AddThread(&MoveBall,10, "Move_Ball");
         gameState.numberOfBalls ++;
     }
     G8RTOS_OS_Sleep(2000);
    }

}


void MoveBall(){

    int i;

    for(i = 0; i<MAX_NUM_OF_BALLS; i++){


        if(!(gameState.balls[i].alive)){


           break;

        }


    }
        int8_t Random_Speed[] = {-2,2,-3,3,-4,4,-5,5,-6,6};

        gameState.balls[i].alive = true;
        gameState.balls[i].color = LCD_WHITE;
        gameState.balls[i].currentCenterX = MAX_SCREEN_X/2;
        gameState.balls[i].currentCenterY = MAX_SCREEN_Y/2;


        int16_t currentVelX = Random_Speed[rand() % 10];
        int16_t currentVelY = Random_Speed[rand() % 10];





        while(1){

            /**************************************************************** Top player collision/scored on ************************************************************************************/
            if ((gameState.balls[i].currentCenterY + currentVelY - BALL_SIZE/2) <= (ARENA_MIN_Y + PADDLE_WID + 2)) {

                //Left  3rd: CenterX - 32 -> CenterX - 11
                if ((gameState.balls[i].currentCenterX >= gameState.players[TOP].currentCenter - 32 + 4) && (gameState.balls[i].currentCenterX < gameState.players[TOP].currentCenter - 11)) {

                    currentVelY = -1 * currentVelY;
                    currentVelX = -1 * abs(currentVelX);
                    if (currentVelX == 0) {
                        currentVelX = -abs(currentVelY);
                    }

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_BLUE;



                }
                //Mid 3rd: CenterX - 11 -> CenterX + 12
                else if ((gameState.balls[i].currentCenterX >= gameState.players[TOP].currentCenter - 11) && (gameState.balls[i].currentCenterX < gameState.players[TOP].currentCenter + 12)) {

                    currentVelY = -1 * currentVelY;
                    currentVelX = 0;

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_BLUE;


                }
                //Right 3rd: CenterX + 12 -> CenterX + 32
                else if ((gameState.balls[i].currentCenterX >= gameState.players[TOP].currentCenter + 12) && (gameState.balls[i].currentCenterX <= gameState.players[TOP].currentCenter + 36)) {
                    currentVelY = -1 * currentVelY;
                    currentVelX = abs(currentVelX);
                    if (currentVelX == 0) {
                        currentVelX = abs(currentVelY);
                    }

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_BLUE;

                }
                // SCORED ON!
                else {
                    if (gameState.balls[i].color == PLAYER_RED) {
                        gameState.LEDScores[BOTTOM] ++;

                        if (gameState.LEDScores[BOTTOM] == WINNING_SCORE) {
                            gameState.overallScores[BOTTOM] ++;
                            PrintOverallScores(false);
                            gameState.DONE = true;
                        }





                    }
                    if (gameState.numberOfBalls != 0) gameState.numberOfBalls --;
                    gameState.balls[i].alive = false;
                    gameState.balls[i].color = LCD_WHITE;
                    G8RTOS_KillSelf();
                }
            }

            /****************************************************************** Bottom player collision/scored on *******************************************************************************/
            else if ((gameState.balls[i].currentCenterY + currentVelY  + BALL_SIZE/2) >= (ARENA_MAX_Y - PADDLE_WID - 2)) {
                //Left  3rd: CenterX - 32 -> CenterX - 11
                if ((gameState.balls[i].currentCenterX >= gameState.players[0].currentCenter - 36) && (gameState.balls[i].currentCenterX < gameState.players[0].currentCenter - 11)) {
                    currentVelY = -1 * currentVelY;
                    currentVelX = -1 * abs(currentVelX);
                    if (currentVelX == 0) {
                        currentVelX = -abs(currentVelY);
                    }

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_RED;

                }
                //Mid   3rd: CenterX - 11 -> CenterX + 12
                else if ((gameState.balls[i].currentCenterX >= gameState.players[0].currentCenter - 11) && (gameState.balls[i].currentCenterX < gameState.players[0].currentCenter + 12)) {
                    currentVelY = -1 * currentVelY;
                    currentVelX = 0;

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_RED;

                }
                //Right 3rd: CenterX + 12 -> CenterX + 32
                else if ((gameState.balls[i].currentCenterX >= gameState.players[0].currentCenter + 12) && (gameState.balls[i].currentCenterX <= gameState.players[0].currentCenter + 36)) {
                    currentVelY = -1 * currentVelY;
                    currentVelX = abs(currentVelX);
                    if (currentVelX == 0) {
                        currentVelX = abs(currentVelY);
                    }

                    if (gameState.balls[i].color == LCD_WHITE) gameState.balls[i].color = PLAYER_RED;

                }
                // SCORED ON!
                else {
                    if (gameState.balls[i].color == PLAYER_BLUE) {
                        gameState.LEDScores[TOP] ++;


                        if (gameState.LEDScores[TOP] == WINNING_SCORE) {
                        gameState.overallScores[TOP] ++;
                        PrintOverallScores(false);
                        gameState.DONE = true;
                        }
                    }
                    if (gameState.numberOfBalls != 0) gameState.numberOfBalls --;
                    gameState.balls[i].alive = false;
                    gameState.balls[i].color = LCD_WHITE;
                    G8RTOS_KillSelf();
                }

            }

            /****************************************************************** Wall Collision *************************************************************************************************/
            else if ((gameState.balls[i].currentCenterX + currentVelX <= ARENA_MIN_X+4) || (gameState.balls[i].currentCenterX + currentVelX >= ARENA_MAX_X-4)) {
                currentVelX = -1 * currentVelX;
            }


            gameState.balls[i].currentCenterY += currentVelY;
            gameState.balls[i].currentCenterX += currentVelX;

            G8RTOS_OS_Sleep(35);

        }
}

void MoveLEDs() {
    uint8_t hostScore_old = 0, hostScore_new = 0;
    uint8_t clientScore_old = 0, clientScore_new = 0;
    uint16_t hostScoreLED = 0, clientScoreLED = 0;

    while(1) {
        hostScore_old = hostScore_new;
        clientScore_old = clientScore_new;
        hostScore_new = gameState.LEDScores[BOTTOM];
        clientScore_new = gameState.LEDScores[TOP];

        if((hostScore_old != hostScore_new) && (clientScore_old != clientScore_new)) {
            for(int i = 0; i < hostScore_new; i++) {
                hostScoreLED |= 1 << i;
            }
            for(int i = 0; i < clientScore_new; i++) {
                clientScoreLED |= 0x8000 >> i;
            }
            G8RTOS_WaitSemaphore(&LED_Score);
            LP3943_LEDSet(RED, hostScoreLED, ON);
            LP3943_LEDSet(BLUE, clientScoreLED, ON);
            G8RTOS_SignalSemaphore(&LED_Score);

        }
        else if(hostScore_old != hostScore_new) {
            for(int i = 0; i < hostScore_new; i++) {
                hostScoreLED |= 1 << i;
            }
            G8RTOS_WaitSemaphore(&LED_Score);
            LP3943_LEDSet(RED, hostScoreLED, ON);
            G8RTOS_SignalSemaphore(&LED_Score);
        }
        else if(clientScore_old != clientScore_new) {
            for(int i = 0; i < clientScore_new; i++) {
                clientScoreLED |= 0x8000 >> i;
            }
            G8RTOS_WaitSemaphore(&LED_Score);
            LP3943_LEDSet(BLUE, clientScoreLED, ON);
            G8RTOS_SignalSemaphore(&LED_Score);
        }
    }
}


void EndOfGameHost() {
    //Let client know

    /*
    G8RTOS_WaitSemaphore(&WIFI);
    // Send Packet
    SendData((uint8_t*)&gameState,gameState.player.IP_address, sizeof(gameState));
    G8RTOS_SignalSemaphore(&WIFI);

    while(!(ClientSpecificInfo.ackEndofGame)) {
        G8RTOS_WaitSemaphore(&WIFI);
        ReceiveData( (_u8*)&ClientSpecificInfo.ackEndofGame, sizeof(ClientSpecificInfo.ackEndofGame));
        G8RTOS_SignalSemaphore(&WIFI);
    }
    */

    G8RTOS_WaitSemaphore(&LCD_USAGE);
    G8RTOS_WaitSemaphore(&LED_Score);
    G8RTOS_WaitSemaphore(&WIFI);

    G8RTOS_KillAllOtherThreads();

    G8RTOS_InitSemaphore(&LCD_USAGE, 1);
    G8RTOS_InitSemaphore(&LED_Score, 1);
    G8RTOS_InitSemaphore(&WIFI, 1);



    int tempScore = 0;

    if(gameState.LEDScores[TOP] > gameState.LEDScores[BOTTOM]){
        for(int i = 0; i< gameState.LEDScores[TOP]; i++) {
            tempScore |= 0x8000 >> i;
        }
        LP3943_LEDSet(BLUE, tempScore, ON);
        LCD_Clear(PLAYER_BLUE);
    }
    else {
        for(int i = 0; i< gameState.LEDScores[BOTTOM]; i++) {
            tempScore |= 1 << i;
        }
        LP3943_LEDSet(RED, tempScore, ON);
        LCD_Clear(PLAYER_RED);
    }
    PrintOverallScores(true);


    LCD_Text(10, 90, "To start a new game, press B0", LCD_WHITE);

    restartFlag = true;

    G8RTOS_AddThread(&IdleThread,  LowestPrioirty, "Idle");

    InitButtons();
      G8RTOS_ADDAPeriodicEvent(&PORT4, ButtonsPriority, PORT4_IRQn);

    G8RTOS_KillSelf();

}

void ReadJoystickHost(){

    // Point type
   point Joy_Stick_Reading;


        while(1){

      GetJoystickCoordinates(&Joy_Stick_Reading.x, &Joy_Stick_Reading.y);

      if(Joy_Stick_Reading.x > 2000){

          gameState.player.displacement = 3;
      }

      else if( Joy_Stick_Reading.x < -2000){

          gameState.player.displacement = -3;
      }

      else{
          gameState.player.displacement =0;
      }



      G8RTOS_OS_Sleep(10);






      // Sleep for 10ms to keep game fair as described in the lab doc.



      gameState.players[BOTTOM].currentCenter += gameState.player.displacement;

      if(gameState.players[BOTTOM].currentCenter > HORIZ_CENTER_MAX_PL){

          gameState.players[BOTTOM].currentCenter = HORIZ_CENTER_MAX_PL;
      }

      else if(gameState.players[BOTTOM].currentCenter < HORIZ_CENTER_MIN_PL){

          gameState.players[BOTTOM].currentCenter = HORIZ_CENTER_MIN_PL;

      }




              gameState.players[TOP].currentCenter +=  ClientSpecificInfo.displacement ;


                    if(gameState.players[TOP].currentCenter > HORIZ_CENTER_MAX_PL){

                        gameState.players[TOP].currentCenter = HORIZ_CENTER_MAX_PL;
                                 }

                                 else if(gameState.players[TOP].currentCenter < HORIZ_CENTER_MIN_PL){

                                     gameState.players[TOP].currentCenter = HORIZ_CENTER_MIN_PL;

                                 }







          G8RTOS_OS_Sleep(5);

        }

            }






void PORT4(){

    if(P4->IFG & BIT4){


        G8RTOS_AddThread(&CreateGame, 30,"CreateGame");

        NVIC_DisableIRQ(PORT4_IRQn);
        NVIC_DisableIRQ(PORT5_IRQn);

    }
}


void SendDataToClient(){




    while(1){

    G8RTOS_WaitSemaphore(&WIFI);
    // Send Packet
    SendData((uint8_t*)&gameState,gameState.player.IP_address, sizeof(gameState));
    G8RTOS_SignalSemaphore(&WIFI);
    if(gameState.DONE == true){
        G8RTOS_AddThread(&EndOfGameHost, 1, "EndOfGameHost");
        gameState.DONE = false;
    }

    G8RTOS_OS_Sleep(5);

    }


   }


void ReceiveDataFromClient(){

while(1){
          G8RTOS_WaitSemaphore(&WIFI);
          ReceiveData( (_u8*)&ClientSpecificInfo.displacement, sizeof(ClientSpecificInfo.displacement));
          G8RTOS_SignalSemaphore(&WIFI);
          G8RTOS_OS_Sleep(5);
    }


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************ClientSpecificInfo's Shit******************************************************************************************************/

void JoinGame(){
    //new game
    if(!restartFlag) {
        LCD_Clear(LCD_BLACK);
        LCD_Text(10,80, "Waiting for Host to join", LCD_RED);
        // Join the other headass as a client
        initCC3100(Client);
        ClientSpecificInfo.IP_address= getLocalIP();
        ClientSpecificInfo.acknowledge = false;
        ClientSpecificInfo.joined = false;
        ClientSpecificInfo.playerNumber =2;
        ClientSpecificInfo.ready = false;
        while(gameState.player.joined == false){
            SendData((uint8_t*)&ClientSpecificInfo, HOST_IP_ADDR, sizeof(ClientSpecificInfo));
            ReceiveData((uint8_t*)&gameState, sizeof(gameState));
        }
        ClientSpecificInfo.acknowledge = true;
        SendData( (uint8_t*)&ClientSpecificInfo, HOST_IP_ADDR, sizeof(ClientSpecificInfo) );
        gameState.overallScores[0] = 0;
        gameState.overallScores[1] = 0;
        LP3943_LEDSet(RED, 0xFFFF, OFF);
        LP3943_LEDSet(BLUE, 0xFFFF, OFF);
        InitBoardState();
        G8RTOS_AddThread( &IdleThread, 255, "My_Idle");
        G8RTOS_AddThread(&ReadJoystickClient, 15,"Read_Host_Stick" );
        G8RTOS_AddThread(&DrawObjects, 10, "Draw_Obj" );
        G8RTOS_AddThread(&MoveLEDs, 25, "MoveLEDs" );
        G8RTOS_AddThread(&ReceiveDataFromHost, 15, "Recieve_Data" );
        G8RTOS_AddThread(&SendDataToHost,15 ,"Send to the other fucker" );
        G8RTOS_KillSelf();
    }
    //restart game
    else {
        while(!gameState.restartGame) {
       //     G8RTOS_WaitSemaphore(&WIFI);
            ReceiveData( (_u8*)&gameState, sizeof(gameState));
         //   G8RTOS_SignalSemaphore(&WIFI);
        }
        LP3943_LEDSet(RED, 0xFFFF, OFF);
        LP3943_LEDSet(BLUE, 0xFFFF, OFF);
        InitBoardState();
        G8RTOS_AddThread( &IdleThread, 255, "My_Idle");
        G8RTOS_AddThread(&ReadJoystickClient, 15,"Read_Host_Stick" );
        G8RTOS_AddThread(&DrawObjects, 10, "Draw_Obj" );
        G8RTOS_AddThread(&MoveLEDs, 25, "MoveLEDs" );
        G8RTOS_AddThread(&ReceiveDataFromHost, 15, "Recieve_Data" );
        G8RTOS_AddThread(&SendDataToHost,15 ,"Send to the other fucker" );
        G8RTOS_KillSelf();
    }

}



void ReadJoystickClient() {


    point Joy_Stick_Reading2;
           while(1){

         GetJoystickCoordinates(&Joy_Stick_Reading2.x, &Joy_Stick_Reading2.y);

         if(Joy_Stick_Reading2.x < -2000){

             ClientSpecificInfo.displacement = 5;
         }

         else if( Joy_Stick_Reading2.x > 2000){

             ClientSpecificInfo.displacement = -5;
         }

         else{
             ClientSpecificInfo.displacement =0;
         }


                  G8RTOS_OS_Sleep(5);




           }

    }




void ReceiveDataFromHost() {

    while(1){

        G8RTOS_WaitSemaphore(&WIFI);
        ReceiveData( (_u8*)&gameState, sizeof(gameState));
        G8RTOS_SignalSemaphore(&WIFI);


        /*
        if(gameState.LEDScores[TOP] == WINNING_SCORE || gameState.LEDScores[BOTTOM] == WINNING_SCORE) {
            ClientSpecificInfo.ackEndofGame = true;
            G8RTOS_WaitSemaphore(&WIFI);
            SendData((uint8_t*)&ClientSpecificInfo.ackEndofGame,HOST_IP_ADDR, sizeof(ClientSpecificInfo.ackEndofGame));
            G8RTOS_SignalSemaphore(&WIFI);
            G8RTOS_AddThread(&EndOfGameClient, 1, "EndOfGameClient");
        }
        */


        if(gameState.DONE == true){
            G8RTOS_AddThread(&EndOfGameClient, 1, "EndOfGameClient");
        }

        G8RTOS_OS_Sleep(5);
    }


}

void EndOfGameClient() {

    G8RTOS_WaitSemaphore(&LCD_USAGE);
    G8RTOS_WaitSemaphore(&LED_Score);
    G8RTOS_WaitSemaphore(&WIFI);

    G8RTOS_KillAllOtherThreads();

    G8RTOS_InitSemaphore(&LCD_USAGE, 1);
    G8RTOS_InitSemaphore(&LED_Score, 1);
    G8RTOS_InitSemaphore(&WIFI, 1);

    int tempScore = 0;

    if(gameState.LEDScores[TOP] > gameState.LEDScores[BOTTOM]){
        for(int i = 0; i< gameState.LEDScores[TOP]; i++) {
            tempScore |= 0x8000 >> i;
        }
        LP3943_LEDSet(BLUE, tempScore, ON);
        LCD_Clear(PLAYER_BLUE);
    }
    else {
        for(int i = 0; i< gameState.LEDScores[BOTTOM]; i++) {
            tempScore |= 1 << i;
        }
        LP3943_LEDSet(RED, tempScore, ON);
        LCD_Clear(PLAYER_RED);
    }
    PrintOverallScores(true);

    LCD_Text(10, 90, "Waiting for host to restart game!", LCD_WHITE);

    restartFlag = true;

    G8RTOS_AddThread(&IdleThread,  LowestPrioirty, "Idle");
    G8RTOS_AddThread(&JoinGame, 30, "JoinGame");

    G8RTOS_KillSelf();

    }

void SendDataToHost() {




while(1){

    G8RTOS_WaitSemaphore(&WIFI);
    SendData((uint8_t*)&ClientSpecificInfo.displacement,HOST_IP_ADDR, sizeof(ClientSpecificInfo.displacement));
    G8RTOS_SignalSemaphore(&WIFI);
    G8RTOS_OS_Sleep(5);

    }


            }









void PORT5(){

    if (P5->IFG & BIT5) {
        playerRole =Client;
        G8RTOS_AddThread(&JoinGame, 30, "JoinGame");
        NVIC_DisableIRQ(PORT5_IRQn);
        NVIC_DisableIRQ(PORT4_IRQn);
    }
}


void PrintOverallScores(bool gameEnd) {

    char str1[4] = {0,0,0,0}; //becasue uint8_t needs 3 digits
    snprintf(str1, 4, "%.1u", gameState.overallScores[TOP]);
    char str2[4] = {0,0,0,0}; //becasue uint8_t needs 3 digits
    snprintf(str2, 4, "%.1u", gameState.overallScores[BOTTOM]);

    if(gameEnd) {
        LCD_Text(10, 30, "Blue Score:", LCD_WHITE);
        LCD_Text(106, 30, str1, LCD_WHITE);
        LCD_Text(10, 60, "Red Score:", LCD_WHITE);
        LCD_Text(106, 60, str2, LCD_WHITE);
    }
    else{
        LCD_Text(10, 20, str1, PLAYER_BLUE);
        LCD_Text(10, 225, str2, PLAYER_RED);
    }

}







