// @Description ReadyMainSelectSet_SW_DELEET_Patch
// @HookAddress 0x91C72
// @HookString 0248 86460248 00470000 8b1c0908 P C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// IRAM
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)

// Subroutine
#define sub_8090F94 ((void (*)(unsigned char, unsigned char)) 0x8090F95)
#define sub_80910EC ((void (*)(unsigned char, unsigned char)) 0x80910ED)
#define sub_80911E0 ((void (*)(unsigned char, unsigned char)) 0x80911E1)

// SRAM (0xE000F00~)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

void ReadyMainSelectSet_SW_DELEET_Patch() {
    // Vanilla code
    sub_8090F94(ucSaveNum, 1);
    sub_80910EC(ucSaveNum, 1);
    sub_80911E0(ucSaveNum, 1);

    // Initialize my variables
    for (int i = 0; i <= 24; i++) {
        high_diamonds_sram[i + (ucSaveNum * 24)] = 0;
    }
}
