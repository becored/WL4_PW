// @Description Wario4InitPatch
// @HookAddress 0x5EE0
// @HookString 01 48 86 46 01 48 00 47 F7 5E 00 08 P C0 46
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000

// IRAM
#define ucPerfect (*(volatile unsigned char*) 0x3000015)
#define s5_car_y (*(volatile unsigned short*) 0x3002C9C)
#define s5_super_hard (*(volatile unsigned short*) 0x3002CA2)

// I/O
#define REG_DISPCNT (*(volatile unsigned short*) 0x4000000)
#define REG_BG0VOFS (*(volatile unsigned short*) 0x4000012)
#define REG_BG0HOFS (*(volatile unsigned short*) 0x4000010)
#define REG_BG1VOFS (*(volatile unsigned short*) 0x4000016)
#define REG_BG1HOFS (*(volatile unsigned short*) 0x4000014)
#define REG_BG2VOFS (*(volatile unsigned short*) 0x400001A)
#define REG_BG2HOFS (*(volatile unsigned short*) 0x4000018)
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

void Wario4InitPatch() {
    // Enable S-Hard for debug (Don't forget to remove before release!)
    // ucPerfect = 1;

    // Vanilla code
    s5_car_y = 150;
    if ( ucPerfect == 1 ) {
        s5_super_hard = 1;
    } else {
        s5_super_hard = 0;
    }
    REG_DISPCNT = 0;
}
