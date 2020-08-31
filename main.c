#include "msp.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "G8RTOS.h"
//#define DEBUG
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

    FILE *in_file;
    MAP Donkey_Kong_Map;
    Monkey Monkey;
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Climing_tree.bin", "rb");
    fread(Donkey_Kong_Map.Climbingtree, sizeof(uint16_t), 490, in_file);
    fclose(in_file);
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Log.bin", "rb");
    fread(Donkey_Kong_Map.log, sizeof(uint16_t), 410, in_file);
    fclose(in_file);
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\water.bin", "rb");
    fread(Donkey_Kong_Map.water, sizeof(uint16_t), 221, in_file);
    fclose(in_file);
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Stand_on_start_grass.bin", "rb");
    fread(Donkey_Kong_Map.standontgrass, sizeof(uint16_t), 176, in_file);
    fclose(in_file);
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Stand_on_start_grass.bin", "rb");
    fread(Donkey_Kong_Map.standontgrass, sizeof(uint16_t), 176, in_file);
    fclose(in_file);
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Stand_on_tree.bin", "rb");
    fread(Donkey_Kong_Map.standontree, sizeof(uint16_t), 713, in_file);
    fclose(in_file);

    
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Mario.bin", "rb");
    fread(Donkey_Kong_Map.Mario, sizeof(uint16_t), 272, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Big_Kong.bin", "rb");
    fread(Donkey_Kong_Map.Big_Kong, sizeof(uint16_t), 1632, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Beast1.bin", "rb");
    fread(Donkey_Kong_Map.Beast1, sizeof(uint16_t), 144, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Beast2.bin", "rb");
    fread(Donkey_Kong_Map.Beast2, sizeof(uint16_t), 187, in_file);
    fclose(in_file);


    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Monkey_Sitting.bin", "rb");
    fread(Monkey.sitting, sizeof(uint16_t), 486, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Monkey_Walking1.bin", "rb");
    fread(Monkey.Walking1, sizeof(uint16_t), 486, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Monkey_Walking2.bin", "rb");
    fread(Monkey.Walking2, sizeof(uint16_t), 486, in_file);
    fclose(in_file);
    
    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Monkey_Climbing.bin", "rb");
    fread(Monkey.climbing1, sizeof(uint16_t), 340, in_file);
    fclose(in_file);

    in_file = fopen("C:\\Users\\Khaled\\Desktop\\UF\\Project\\Donkey_Kong\\Monkey_Climbing2.bin", "rb");
    fread(Monkey.climbing2, sizeof(uint16_t), 420, in_file);
    fclose(in_file);
    



#ifndef DEBUG

    Kong_map_ptr = &Donkey_Kong_Map;
    Monkey_ptr = &Monkey;
    G8RTOS_Init();
    G8RTOS_AddThread(&Start_game, 2, "Start me");
    G8RTOS_Launch();

#else

 G8RTOS_Init();
 LCD_Clear(LCD_BLACK);

 int index =0;
 for(int i=0; i<17; i++){

     for(int j =0; j<20; j++){
         LCD_SetPoint(j+50,i+50,Monkey.climbing1[index]);
         index +=1; 
     }
 }



#endif
}
