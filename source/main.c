#include <nds.h>
#include <stdio.h>
#include "pikachu_standard.h"

int main(int argc, char **argv) {
    PrintConsole bottomConsole;
    
    videoSetMode(MODE_1_2D | DISPLAY_BG2_ACTIVE);
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);
    
    BGCTRL[2] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_COLOR_256 | BG_RS_64x64;
    
    dmaCopy(pikachu_standardTiles, (void *)CHAR_BASE_BLOCK(1), pikachu_standardTilesLen);
    dmaCopy(pikachu_standardMap, (void *)SCREEN_BASE_BLOCK(0), pikachu_standardMapLen);
    dmaCopy(pikachu_standardPal, BG_PALETTE, pikachu_standardPalLen);
    
    bgSetCenter(2, 96, 64);
    bgSetScale(2, 256, 256);
    
    consoleInit(&bottomConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    
    consoleSelect(&bottomConsole);
    iprintf("X:0         8        16       24\n");
    iprintf("0 +---------+--------+--------+\n");
    iprintf("1 |         |        |        |\n");
    iprintf("2 |         |        |        |\n");
    iprintf("3 |         |        |        |\n");
    iprintf("4 |         |        |        |\n");
    iprintf("5 |         |        |        |\n");
    iprintf("6 |         |        |        |\n");
    iprintf("7 |         |        |        |\n");
    iprintf("8 +---------+--------+--------+\n");
    iprintf("9 |         |        |        |\n");
    iprintf("10|         |        |        |\n");
    iprintf("11+---------+--------+--------+\n");
    iprintf("\n");
    iprintf("Pikachu: centered\n");
    iprintf("BG2 affine 64x64\n");
    iprintf("\n");
    iprintf("Start: Pika pika\n");
    
    while(1) {
        scanKeys();
        if (keysDown() & KEY_START) {
            consoleSelect(&bottomConsole);
            iprintf("Playing...\n");
        }
        swiWaitForVBlank();
    }
    
    return 0;
}