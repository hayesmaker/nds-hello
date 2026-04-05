#include <nds.h>
#include <stdio.h>
#include <stdlib.h>

#define PIKACHU_SIZE SpriteSize_32x32
#define PIKACHU_WIDTH  32
#define PIKACHU_HEIGHT 32

static const unsigned int pikachu_palette[16] = {
    0x000000,
    0xFFFF00,
    0xFF0000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
    0x000000,
};

static const unsigned int pikachu_gfx[PIKACHU_HEIGHT * PIKACHU_WIDTH / 2] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x11110000, 0x11110000, 0x00000000,
    0x00000000, 0x11110000, 0x11110000, 0x00000000,
    0x00000000, 0x01111000, 0x01111000, 0x00000000,
    0x00000000, 0x00111100, 0x00111100, 0x00000000,
    0x00000000, 0x00111100, 0x00111100, 0x00000000,
    0x00000000, 0x00011110, 0x00011110, 0x00000000,
    0x00000000, 0x00001111, 0x00001111, 0x00000000,
    0x00000000, 0x00000111, 0x00000111, 0x00000000,
    0x00000000, 0x00000011, 0x00000011, 0x00000000,
    0x00000000, 0x00000011, 0x00000011, 0x00000000,
    0x00000000, 0x00000011, 0x00000011, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

int main(int argc, char **argv) {
    consoleInit(NULL, 0, LCD_BOTH);
    consoleClear();
    
    printf("  ====================\n");
    printf("  Pikachu Hello World!\n");
    printf("  ====================\n\n");
    printf("  TOP SCREEN: Graphics\n");
    printf("  BOTTOM: Console\n\n");
    printf("  Controls:\n");
    printf("  - START: Exit\n\n");
    printf("  Building DS Homebrew!\n");
    
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankA(VRAM_A_MAIN_SPRITE);
    
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    
    int spriteId = 0;
    
    oamSet(&oamMain, 
           spriteId,
           96,
           80,
           0,
           PIKACHU_SIZE,
           SpriteColorFormat_16Color,
           pikachu_gfx,
           0,
           false,
           false,
           false,
           false,
           false);
    
    oamSetPalette(&oamMain, 0, pikachu_palette);
    
    oamUpdate(&oamMain);
    
    while(1) {
        scanf();
        
        if (keysDown() & KEY_START) break;
        
        swiWaitForVBlank();
        oamUpdate(&oamMain);
    }
    
    return 0;
}
