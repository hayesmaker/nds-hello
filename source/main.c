#include <nds.h>
#include <stdio.h>
#include <string.h>
#include "pikachu_sprite_clean.h"

int spriteX = 96;
int spriteY = 64;

int main(int argc, char **argv) {
    PrintConsole bottomConsole;
    
    videoSetMode(MODE_0_2D | DISPLAY_SPR_ACTIVE);
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankE(VRAM_E_MAIN_SPRITE);
    vramSetBankC(VRAM_C_SUB_BG);
    
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    
    u16* spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    memcpy(spriteGfx, pikachu_sprite_cleanTiles, pikachu_sprite_cleanTilesLen);
    memcpy(SPRITE_PALETTE, pikachu_sprite_cleanPal, pikachu_sprite_cleanPalLen);
    
    consoleInit(&bottomConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    
    consoleSelect(&bottomConsole);
    iprintf("D-PAD: Move sprite\n");
    iprintf("A: +8  B: -8\n");
    iprintf("START: Quit\n");
    
    while(1) {
        scanKeys();
        int held = keysHeld();
        
        if (held & KEY_UP) spriteY -= 2;
        if (held & KEY_DOWN) spriteY += 2;
        if (held & KEY_LEFT) spriteX -= 2;
        if (held & KEY_RIGHT) spriteX += 2;
        
        if (keysDown() & KEY_A) spriteX += 8;
        if (keysDown() & KEY_B) spriteX -= 8;
        
        if (spriteX < 0) spriteX = 0;
        if (spriteY < 0) spriteY = 0;
        if (spriteX > 256) spriteX = 256;
        if (spriteY > 192) spriteY = 192;
        
        oamSet(&oamMain, 0, spriteX, spriteY, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
               spriteGfx, -1, false, false, false, false, false);
        
        consoleSelect(&bottomConsole);
        iprintf("\x1b[3;0H");
        iprintf("X:%d Y:%d    \n", spriteX, spriteY);
        
        if (keysDown() & KEY_START) break;
        
        swiWaitForVBlank();
        oamUpdate(&oamMain);
    }
    
    return 0;
}