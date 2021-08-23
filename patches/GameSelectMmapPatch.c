// @Description GameSelectMmapPatch
// @HookAddress 0x7A0B8
// @HookString 01 48 86 46 01 48 00 47 6B A3 07 08 P C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
#define	KEY_L		0x200 // L
#define	KEY_R		0x100 // R
#define	KEY_A		0x001 // A
#define	KEY_B		0x002 // B
#define	KEY_DOWN	0x080 // Down
#define	KEY_UP		0x040 // Up
#define	KEY_LEFT	0x020 // Left
#define	KEY_RIGHT	0x010 // Right
#define	KEY_START	0x008 // Start
#define	KEY_SELECT	0x004 // Select
#define	KEY_ALL		0x3FF // Any key

#define VRAM 0x6000000
#define SPACE_CHAR 0x869EE68
#define DIAMOND_CHAR 0x869F8C8
#define SLASH_CHAR 0x869F928
#define NUM_CHAR 0x869FC88

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define sGameSeq (*(volatile unsigned char*) 0x3000C3C)
#define ADDR_KEY_4 (*(volatile unsigned short*) 0x3001848)
#define bSelIdoFlg (*(volatile unsigned char*) 0x3003C45)
#define ucSelectVector ((volatile unsigned char*) 0x3004700) // 1: into passage, 3: back from passage, 4: into boss level
#define high_diamonds ((volatile unsigned char*) 0x3006F80)

// I/O
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// VRAM
#define map_diamond (*(volatile unsigned short*) 0x600C424)
#define map_num_digit1 (*(volatile unsigned short*) 0x600C428)
#define map_num_digit2 (*(volatile unsigned short*) 0x600C42A)
#define map_slash (*(volatile unsigned short*) 0x600C42C)
#define map_max_digit1 (*(volatile unsigned short*) 0x600C42E)
#define map_max_digit2 (*(volatile unsigned short*) 0x600C430)

// Subroutine
#define sub_8001DA4_m4aSongNumStart ((void (*)(int)) 0x8001DA5)
#define sub_80845F0 ((int (*)()) 0x80845F1)
#define sub_807A700 ((int (*)()) 0x807A701)

// SRAM
#define KilledEnemiesCounterRooms ((volatile unsigned char*) 0xE000E00)
#define high_diamond (*(volatile unsigned char*) 0xE000E28)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

const char high_diamonds_max[] = {6, 0, 0, 0, 4, 11, 9, 10, 8, 10, 10, 9, 11, 9, 9, 7, 11, 9, 9, 9, 6, 0, 0, 0, 6, 0, 0, 0, 3, 7, 7, 6, 4, 7, 8, 6, 9, 6, 5, 4, 8, 6, 8, 9, 6, 0, 0, 0, 6, 0, 0, 0, 2, 6, 8, 5, 4, 6, 7, 5, 8, 5, 4, 3, 8, 4, 7, 9, 4, 0, 0, 0};
//                                ^Normal                                                                       ^Hard                                                                   ^S-Hard

void GameSelectMmapPatch() {
    // Vanilla code
    if (sub_80845F0() && sub_807A700()) {
        sGameSeq = 0x24;
    }

    // Initialize my variables
    for (int i = 0; i <= 255; i++) {
        KilledEnemiesCounterRooms[i] = 0;
    }

    // Map
    map_diamond = 0x8154;
    map_num_digit1 = 0xE155;
    map_num_digit2 = 0xE156;
    map_slash = 0xE157;
    map_max_digit1 = 0xE158;
    map_max_digit2 = 0xE159;

	// Hidden VRAM
	if (ucSelectVector[0] == 1 || ucSelectVector[0] == 3 || bSelIdoFlg == 1 || InPassageLevelID > 3) {
		for(int i = 0; i < 6 ; i ++) {
            REG_DMA3SAD = SPACE_CHAR;
            REG_DMA3DAD = (VRAM + 0x2A80 + (i * 0x20));
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
		}
	} else {
        // Show VRAM
        int i = (PassageID * 4) + InPassageLevelID;
        // Diamond Icon
        REG_DMA3SAD = DIAMOND_CHAR;
        REG_DMA3DAD = (VRAM + 0x2A80);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // 2-digit (High Diamonds)
        if (high_diamonds_sram[i + (ucSaveNum * 24)] < 10) {
            REG_DMA3SAD = NUM_CHAR;
        } else {
            REG_DMA3SAD = NUM_CHAR + 0x20;
        }
        REG_DMA3DAD = (VRAM + 0x2AA0);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // 1-digit (High Diamonds)
        if (high_diamonds_sram[i + (ucSaveNum * 24)] < 10) {
            REG_DMA3SAD = NUM_CHAR + (high_diamonds_sram[i + (ucSaveNum * 24)] * 0x20);
        } else {
            REG_DMA3SAD = NUM_CHAR + ((high_diamonds_sram[i + (ucSaveNum * 24)] - 10) * 0x20);
        }
        REG_DMA3DAD = (VRAM + 0x2AC0);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // Slash
        REG_DMA3SAD = SLASH_CHAR;
        REG_DMA3DAD = (VRAM + 0x2AE0);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // 2-digit (Max Diamonds)
        if (high_diamonds_max[i + (CurrentDifficulty * 24)] < 10) {
            REG_DMA3SAD = NUM_CHAR;
        } else {
            REG_DMA3SAD = NUM_CHAR + 0x20;
        }
        REG_DMA3DAD = (VRAM + 0x2B00);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // 1-digit (Max Diamonds)
        if (high_diamonds_max[i + (CurrentDifficulty * 24)] < 10) {
            REG_DMA3SAD = NUM_CHAR + (high_diamonds_max[i + (CurrentDifficulty * 24)] * 0x20);
        } else {
            REG_DMA3SAD = NUM_CHAR + ((high_diamonds_max[i + (CurrentDifficulty * 24)] - 10) * 0x20);
        }
        REG_DMA3DAD = (VRAM + 0x2B20);
        REG_DMA3CNT = 0x80000010;
        while (REG_DMA3CNT & 0x80000000) ;
        // Palette change (Diamond Icon)
        if (high_diamonds_sram[i + (ucSaveNum * 24)] >= high_diamonds_max[i + (CurrentDifficulty * 24)]) {
            map_diamond = 0xD154;
        }
    }
}
