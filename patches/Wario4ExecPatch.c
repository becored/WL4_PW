// @Description Wario4ExecPatch
// @HookAddress 0x3694
// @HookString 01 48 86 46 01 48 00 47 07 39 00 08 P C0 46 C0 46 C0 46 C0 46
// Mode: Thumb
// Made by beco

// Data
#define VRAM 0x6000000

// IRAM
#define ucPerfect (*(volatile unsigned char*) 0x3000015)
#define usFadeTimer (*(volatile unsigned short*) 0x300188E)

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

// Subroutine
#define Sub_8005F1C_Wario4_Exec ((void (*)(int)) 0x8005F1D)

void Wario4ExecPatch() {
    // Vanilla code
    Sub_8005F1C_Wario4_Exec( usFadeTimer++ );
}
