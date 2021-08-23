// @Description Diamond(Child) counter
// @HookAddress 0x78EA14
// @HookString P
// Made by beco
// Verison 1.0

struct ENEMY_DATA {
    char PAD1[28];
    char AnimationID;
    char PAD2[15];
};

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define CurrentEnemy (*(volatile struct ENEMY_DATA*) 0x3000A24)

// Subroutine
#define sub_802C5DC ((void (*)()) 0x802C5DD)
#define EntityCollision ((int (*)(int, int)) 0x8026211)

// SRAM
#define KilledEnemiesCounterRooms ((volatile unsigned char*) 0xE000E00)
#define high_diamond (*(volatile unsigned char*) 0xE000E28)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

void DiamondChildCounter() {
    // Vanilla code for diamond GFX
    sub_802C5DC();

    // Diamond counter function
    if (CurrentEnemy.AnimationID == 0x31) {
        int i = (PassageID * 4) + InPassageLevelID;
        high_diamond ++;
        if (high_diamonds_sram[i + (ucSaveNum * 24)] < high_diamond) {
            high_diamonds_sram[i + (ucSaveNum * 24)] = high_diamond;
        }
    }
}
