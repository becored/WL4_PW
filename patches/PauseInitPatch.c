// @Description PauseInitPatch
// @HookAddress 0x88DEC
// @HookString 01 48 86 46 01 48 00 47 11 8E 08 08 P C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000
#define SPACE_CHAR 0x86D67B8
#define DIAMOND_CHAR 0x86D6B78
#define SLASH_CHAR 0x86D6BD8
#define NUM_CHAR 0x86D6E78

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sDmapWindowUpY (*(volatile unsigned short*) 0x3003C50)
#define sDmapWindowDownY (*(volatile unsigned short*) 0x3003C52)

// I/O
#define REG_BG0VOFS (*(volatile unsigned short*) 0x4000012)
#define REG_BG0HOFS (*(volatile unsigned short*) 0x4000010)
#define REG_BG1VOFS (*(volatile unsigned short*) 0x4000016)
#define REG_BG1HOFS (*(volatile unsigned short*) 0x4000014)
#define REG_BG2VOFS (*(volatile unsigned short*) 0x400001A)
#define REG_BG2HOFS (*(volatile unsigned short*) 0x4000018)
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// VRAM
#define map_diamond (*(volatile unsigned short*) 0x600C1AC)
#define map_num_digit1 (*(volatile unsigned short*) 0x600C1B0)
#define map_num_digit2 (*(volatile unsigned short*) 0x600C1B2)
#define map_slash (*(volatile unsigned short*) 0x600C1B4)
#define map_max_digit1 (*(volatile unsigned short*) 0x600C1B6)
#define map_max_digit2 (*(volatile unsigned short*) 0x600C1B8)

// SRAM
#define high_diamond (*(volatile unsigned char*) 0xE000E28)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

const char high_diamonds_max[] = {6, 0, 0, 0, 4, 11, 9, 10, 8, 10, 10, 9, 11, 9, 9, 7, 11, 9, 9, 9, 6, 0, 0, 0, 6, 0, 0, 0, 3, 7, 7, 6, 4, 7, 8, 6, 9, 6, 5, 4, 8, 6, 8, 9, 6, 0, 0, 0, 6, 0, 0, 0, 2, 6, 8, 5, 4, 6, 7, 5, 8, 5, 4, 3, 8, 4, 7, 9, 4, 0, 0, 0};
//                                ^Normal                                                                       ^Hard                                                                   ^S-Hard

void PauseInitPatch() {
    // Map
    map_diamond = 0x515A;
    map_num_digit1 = 0xD15B;
    map_num_digit2 = 0xD15C;
    map_slash = 0xD15D;
    map_max_digit1 = 0xD15E;
    map_max_digit2 = 0xD15F;

    // Show VRAM
    int i = (PassageID * 4) + InPassageLevelID;
    // Diamond Icon
    REG_DMA3SAD = DIAMOND_CHAR;
    REG_DMA3DAD = (VRAM + 0x2B40);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;
    // 2-digit (High Diamonds)
    if (high_diamond < 10) {
        REG_DMA3SAD = NUM_CHAR;
    } else {
        REG_DMA3SAD = NUM_CHAR + 0x20;
    }
    REG_DMA3DAD = (VRAM + 0x2B60);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;
    // 1-digit (High Diamonds)
    if (high_diamond < 10) {
        REG_DMA3SAD = NUM_CHAR + (high_diamond * 0x20);
    } else {
        REG_DMA3SAD = NUM_CHAR + ((high_diamond - 10) * 0x20);
    }
    REG_DMA3DAD = (VRAM + 0x2B80);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;
    // Slash
    REG_DMA3SAD = SLASH_CHAR;
    REG_DMA3DAD = (VRAM + 0x2BA0);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;

    // 2-digit (Max Diamonds)
    if (high_diamonds_max[i + (CurrentDifficulty * 24)] < 10) {
        REG_DMA3SAD = NUM_CHAR;
    } else {
        REG_DMA3SAD = NUM_CHAR + 0x20;
    }
    REG_DMA3DAD = (VRAM + 0x2BC0);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;
    // 1-digit (Max Diamonds)
    if (high_diamonds_max[i + (CurrentDifficulty * 24)] < 10) {
        REG_DMA3SAD = NUM_CHAR + (high_diamonds_max[i + (CurrentDifficulty * 24)] * 0x20);
    } else {
        REG_DMA3SAD = NUM_CHAR + ((high_diamonds_max[i + (CurrentDifficulty * 24)] - 10) * 0x20);
    }
    REG_DMA3DAD = (VRAM + 0x2BE0);
    REG_DMA3CNT = 0x80000010;
    while (REG_DMA3CNT & 0x80000000) ;

    // Vanilla code
    sDmapWindowUpY = 160;
    sDmapWindowDownY = 160;
    REG_BG0VOFS = 0;
    REG_BG0HOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG2HOFS = 0;
}
