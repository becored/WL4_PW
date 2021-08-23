// @Description Rewritten_Sub_807687C_DieTekiCoinSet
// @HookAddress 0x7687E
// @HookString 02 48 86 46 02 48 00 47 00 00 AF 68 07 08 P
// Mode: Thumb
// Made by beco

/* Patch & Hook details
.thumb
    .dcb 1
    ldr r0, .DATA
    mov lr, r0
    ldr r0, .DATA + 4
    bx r0
    .dcb 1
.DATA:
    .word 0x080768AF
    .word 0xAAAAAAAA
 */

#define Sub_80767DC_ScoreBunCoinDasu ((void (*)(unsigned short, unsigned short, int)) 0x80767DD)
#define Sub_801E328_EnemyChildSet ((void (*)(unsigned char, unsigned char, unsigned char, unsigned short, unsigned short)) 0x801E329)

#define CurrentLevel (*(volatile unsigned char*) 0x3000003) // 00(first lvl) 01(second lvl) 02(third lvl) 03(fourth lvl) 04(Boss) 05(Mini-Game Shop)
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define CurrentRoom (*(volatile unsigned char*) 0x03000024)
#define ucTekiKillCnt (*(volatile unsigned char*) 0x3000C06)

// SRAM (0xE000E00~) *Will be removed in passage screen
#define KilledEnemiesCounterRooms ((volatile unsigned char*) 0xE000E00) // save A: 0x3006F00(Room00) - 0x3006F0F(Room15), save B: 0x3006F10(Room00) - 0x3006F1F(Room15)

__attribute__((no_caller_saved_registers))
void DieTekiCoinSetPatch(unsigned char k, unsigned short y, unsigned short x, int num) {
    ++ucTekiKillCnt; // Vanilla code
    ++KilledEnemiesCounterRooms[CurrentRoom + (ucSaveNum * 16)]; // Kill enemy counter for each room
    if(!num || CurrentLevel == 4) return; // Disable enemy drops in boss level
    Sub_80767DC_ScoreBunCoinDasu(y, x, num); // Vanilla code
    Sub_801E328_EnemyChildSet(13, 0, 0, y, x); // Vanilla code
}
