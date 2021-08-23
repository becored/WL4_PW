// @Description GameDeletePatch
// @HookAddress 0x9286C
// @HookString 01 48 86 46 01 48 00 47 CB 28 09 08 P C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// IRAM
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sGameSeq (*(volatile unsigned short*) 0x3000C3C)
#define cNextFlg (*(volatile unsigned char*) 0x3000C3E)
#define usFadeTimer (*(volatile unsigned short*) 0x300188E)

// I/O
#define REG_BLDCNT (*(volatile unsigned short*) 0x4000050)

// Subroutine
#define sub_80928E4 ((int (*)()) 0x80928E5)

// SRAM (0xE000F00~)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

void GameDeletePatch() {
    // Vanilla code
    cNextFlg = sub_80928E4();
    if ( cNextFlg ) {
        ++sGameSeq;
        usFadeTimer = 0;
        if ( cNextFlg != 1 ) {
            REG_BLDCNT = 255;
        }
    }

    // Initialize my variables
    if ( cNextFlg ) {
        for (int i = 0; i <= 255; i++) {
            high_diamonds_sram[i] = 0;
        }
    }

}
