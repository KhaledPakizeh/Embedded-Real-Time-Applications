/*
 * game.c
 *
 *  Created on: Aug 28, 2020
 *      Author: Khaled
 */

#include "game.h"
bool Flag = false;
void Start_game()
{

    Draw_map();
    G8RTOS_InitSemaphore(&LCD_USAGE, 1);
    G8RTOS_AddThread(&IDLE, 255, "IDLE");
    G8RTOS_AddThread(&Draw_Objects, 3, "Draw my monkey");
    G8RTOS_AddThread(&Read_stcik, 4, "Read JoyStick");
    G8RTOS_KillSelf();
}

void IDLE()
{

    while (1);
}

void Draw_Objects()
{

    while (1)
    {

        Update_Player(Monkey_ptr);
        G8RTOS_OS_Sleep(50);
    }
}

void Draw_map()
{
    LCD_Clear(LCD_BLACK);
    int start = 0;
    int index = 0;
    /******************* Water *********************************************/
    for (int x = 0; x < 18; x++)
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 17; j++)
            {

                LCD_SetPoint(start + j, MAX_SCREEN_Y - water_highet + i, Kong_map_ptr->water[index]);
                index += 1;
            }
        }
        start += 18;
        index = 0;
    }

    /******************* Climbing Trees *********************************************/

    int startX = 20;
    int startY = 70;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }

    startX = 50;
    startY = 70;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }

      startX = 80;
    startY = 125;
    index = 0;
   
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }

    startX = 130;
    startY = 70;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }
    startX = 170;
    startY = 70;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }

    startX = 200;
    startY = 75;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }

    startX = 230;
    startY = 75;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }
    startX = 245;
    startY = 50;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }

    startX = 300;
    startY = 50;
    index = 0;
    for (int y = 0; y < 2; y++)
    {
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (!(y == 1 && i > 50))
                    LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Climbingtree[index]);
                index += 1;
            }
        }
        startY += 70;
        index = 0;
    }



    /******************* Logs *********************************************/
    startX = 60;
    startY = 155;
    index = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
                index += 1;
            }
        }
        index = 0;
        startX += 41;
    }
    startX = 60;
    startY = 115;
    index = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 41; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
            index += 1;
        }
    }

    startX = 0;
    startY = 60;
    index = 0;
    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
                index += 1;
            }
        }
        startX += 41;
        index = 0;
    }

    startX = 41 * 4 - 5;
    startY = 70;
    index = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
                index += 1;
            }
        }
        startX += 41;
        index = 0;
    }

    startX = 320 - 41 * 2 - 2;
    startY = 40;
    index = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
                index += 1;
            }
        }
        startX += 41;
        index = 0;
    }
    startX = 320 - 41 * 2 - 2;
    startY = 140;
    index = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->log[index]);
                index += 1;
            }
        }
        startX += 41;
        index = 0;
    }

  

    /******************* Grass *********************************************/
    startX = 0;
    startY = 218;
    index = 0;

    for (int x = 0; x < 3; x++)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 22; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->standontgrass[index]);
                index += 1;
            }
        }
        index = 0;
        startX += 22;
    }

    startX = 120;
    index = 0;
    startY = 204;
    /******************* Tree *********************************************/
    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i < 23; i++)
        {
            for (int j = 0; j < 31; j++)
            {

                LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->standontree[index]);
                index += 1;
            }
        }
        index = 0;
        startX = startX + 31 + 15;
    }

    /************************************ Draw Mario for first time ****************************/
    startX = 120;
    startY = 43;
    index = 0;

    for (int i = 0; i < Mario_Attack_Mode_h; i++)
    {
        for (int j = 0; j < Mario_Attack_Mode_w; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Mario[index]);
            index += 1;
        }
    }
    /************************************ Draw Big_Kong for first time ****************************/
    startX = 70;
    startY = 25;
    index = 0;
    for (int i = 0; i < Big_Kong_H; i++)
    {
        for (int j = 0; j < Big_Kong_W; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Big_Kong[index]);
            index += 1;
        }
    }
    /************************************ Draw Beasts for first time ****************************/

    startX = 135;
    startY = 50;
    index = 0;
    for (int i = 0; i < Beast1_H; i++)
    {
        for (int j = 0; j < Beast1_W; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Beast1[index]);
            index += 1;
        }
    }

    startX = 260;
    startY = 28;
    index = 0;
    for (int i = 0; i < Beast2_H; i++)
    {
        for (int j = 0; j < Beast2_W; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Beast2[index]);
            index += 1;
        }
    }


    startX = 70;
    startY = 103;
    index = 0;
    for (int i = 0; i < Beast2_H; i++)
    {
        for (int j = 0; j < Beast2_W; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Kong_map_ptr->Beast2[index]);
            index += 1;
        }
    }


    /************************************ Draw Moneky for first time ****************************/
    startX = 0;
    startY = 200;
    index = 0;
    Monkey_ptr->Old_Center.x = 0;
    Monkey_ptr->Old_Center.y = 200;
    Monkey_ptr->Center.y = 200;
    Monkey_ptr->Center.x = 0;
    Monkey_ptr->Old_Case = Stand_Still;
    Monkey_ptr->Case = Stand_Still;
    for (int i = 0; i < Monkey_still_highet; i++)
    {
        for (int j = 0; j < Monkey_still_width; j++)
        {

            LCD_SetPoint(startX + j, startY + i, Monkey_ptr->sitting[index]);
            index += 1;
        }
    }
}

void Update_Player()
{

    Monkey_ptr->Old_Case = Monkey_ptr->Case;
    Monkey_ptr->Old_Center.x = Monkey_ptr->Center.x;
    Monkey_ptr->Old_Center.y = Monkey_ptr->Center.y;

    if (Monkey_ptr->Offset.x > 0)
    {

        if (Monkey_ptr->Old_Center.x + 3 <= 35)
        {
            Monkey_ptr->Center.x += 3;
            if (Monkey_ptr->Old_Case == Walk_f1)
            {
                Monkey_ptr->Case = Walk_f2;
            }
            else
            {
                Monkey_ptr->Case = Walk_f1;
            }
        }
    }
    else if (Monkey_ptr->Offset.x < 0)
    {

        if (Monkey_ptr->Old_Center.x - 3 >= 0)
        {
            Monkey_ptr->Center.x -= 3;
            if (Monkey_ptr->Old_Case == Walk_f1)
            {
                Monkey_ptr->Case = Walk_f2;
            }
            else
            {
                Monkey_ptr->Case = Walk_f1;
            }
        }
    }

    else if (Monkey_ptr->Offset.x == 0)
    {
        Monkey_ptr->Case = Stand_Still;
    }

    if (Monkey_ptr->Center.x != Monkey_ptr->Old_Center.x || Monkey_ptr->Center.y != Monkey_ptr->Old_Center.y || Monkey_ptr->Old_Case != Monkey_ptr->Case)
    {
        int index;
        if (Monkey_ptr->Old_Case == Stand_Still)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Old_Center.x + j, Monkey_ptr->Old_Center.y + i, LCD_BLACK);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }

        else if (Monkey_ptr->Old_Case == Walk_f1)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Old_Center.x + j, Monkey_ptr->Old_Center.y + i, LCD_BLACK);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }

        else if (Monkey_ptr->Old_Case == Walk_f2)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Old_Center.x + j, Monkey_ptr->Old_Center.x + i, LCD_BLACK);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }

        if (Monkey_ptr->Case == Stand_Still)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Center.x + j, Monkey_ptr->Center.y + i, Monkey_ptr->sitting[index]);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }

        else if (Monkey_ptr->Case == Walk_f1)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Center.x + j, Monkey_ptr->Center.y + i, Monkey_ptr->Walking1[index]);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }

        else if (Monkey_ptr->Case == Walk_f2)
        {
            index = 0;
            for (int i = 0; i < Monkey_still_highet; i++)
            {
                for (int j = 0; j < Monkey_still_width; j++)
                {
                    G8RTOS_WaitSemaphore(&LCD_USAGE);
                    LCD_SetPoint(Monkey_ptr->Center.x + j, Monkey_ptr->Center.y + i, Monkey_ptr->Walking2[index]);
                    G8RTOS_SignalSemaphore(&LCD_USAGE);
                    index += 1;
                }
            }
        }
    }
}

void Read_stcik()
{

    PointLoc Joy_Stick_Reading;

    while (1)
    {

        GetJoystickCoordinates(&Joy_Stick_Reading.x, &Joy_Stick_Reading.y);

        if (Joy_Stick_Reading.x < -2000)
        {

            Monkey_ptr->Offset.x = 3;
        }

        else if (Joy_Stick_Reading.x > 2000)
        {
            Monkey_ptr->Offset.x = -3;
        }

        else
        {
            Monkey_ptr->Offset.x = 0;
        }

        G8RTOS_OS_Sleep(100);
    }
}
