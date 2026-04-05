#include <nds.h>
#include <stdio.h>

int main(int argc, char **argv) {
    PrintConsole topScreen;
    PrintConsole bottomScreen;
    
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);
    
    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    
    consoleSelect(&topScreen);
    iprintf("\n\n\t====================\n");
    iprintf("\tPikachu Hello World!\n");
    iprintf("\t====================\n");
    
    consoleSelect(&bottomScreen);
    iprintf("\n  TOP SCREEN: Text Demo\n");
    iprintf("  BOTTOM: This console\n\n");
    iprintf("  Controls:\n");
    iprintf("  - START: Exit\n\n");
    iprintf("  Building DS Homebrew!\n");
    
    while(1) {
        if (keysDown() & KEY_START) break;
        swiWaitForVBlank();
    }
    
    return 0;
}