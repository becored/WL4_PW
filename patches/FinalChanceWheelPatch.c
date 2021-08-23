// @Description FinalChanceWheelPatch
// @HookAddress 0x78E974
// @HookString P
// Made by beco
// Verison 1.0

struct ENEMY_DATA {
    unsigned short CurEnemy_orientation;
    unsigned char field_2;
    unsigned char field_3;
    unsigned long OAMDataPackPointerForCurrentAnimation;
    unsigned short CurEnemy_YPos;
    unsigned short CurEnemy_XPos;
    unsigned short CurEnemy_AffinePA;
    unsigned short CurEnemy_AffinePB;
    unsigned short CurEnemy_AffinePC;
    unsigned short CurEnemy_AffinePD;
    unsigned short CurEnemy_CurrentAnimationFrameId;
    unsigned char CurEnemy_RealFrameCountForCurrentAnimationFrame;
    unsigned char CurEnemy_GlobalId;
    unsigned char CurEnemy_RoomEntitySlotId;
    unsigned char CurEnemy_ucChrOfs;
    unsigned char CurEnemy_Prio;
    unsigned char CurEnemy_paletteId;
    unsigned char CurrentAnimationId;
    unsigned char CurEnemy_Life;
    unsigned char CurEnemy_GuardAndDamageParam;
    unsigned char CurEnemy_DisableInteractionWithWarioCountdown;
    unsigned char CurEnemy_SizeY0_Bottom;
    unsigned char CurEnemy_SizeY1_Top;
    unsigned char CurEnemy_SizeX_LeftRight;
    unsigned char CurEnemy_HitboxY0;
    unsigned char CurEnemy_HitboxY1;
    unsigned char CurEnemy_HitboxX0;
    unsigned char CurEnemy_HitboxX1;
    unsigned char CurEnemy_padding;
};

// IRAM
#define PassageID (*(volatile unsigned char*) 0x3000002)
#define InPassageLevelID (*(volatile unsigned char*) 0x3000003)
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define CurrentRoomId (*(volatile unsigned char*) 0x03000024)
#define Switch1Flag (*(volatile unsigned char*) 0x300002F)
#define Switch2Flag (*(volatile unsigned char*) 0x3000030)
#define Switch3Flag (*(volatile unsigned char*) 0x3000031)
#define Switch4Flag (*(volatile unsigned char*) 0x3000032)
#define EntityLeftOverStateList ((volatile unsigned char*) 0x3000564)
#define CurrentEnemyData (*(volatile struct ENEMY_DATA*) 0x3000A24)
#define ScEbuf ((volatile unsigned char*) 0x3000B80) // 12 bytes
#define ScEbufCounter (*(volatile unsigned char*) 0x3000B86) // The Big Board counter
#define ScEbufYPos (*(volatile unsigned short*) 0x3000B88) // 2 bytes, default: 0x0210
#define ScEbufXPos (*(volatile unsigned short*) 0x3000B8A) // 2 bytes, default: 0x0040
#define Scbuf_ucAnmTimer (*(volatile unsigned char*) 0x3000BE1)
#define Scbuf_ucSeq (*(volatile unsigned char*) 0x3000BE3)
#define roulette_current_case_type (*(volatile unsigned short*) 0x3000C10)
#define roulette_moving_case_OAM_gfx (*(volatile unsigned short*) 0x3001470)
#define usWarStopFlg (*(volatile unsigned short*) 0x30019F6)

// Subroutine
#define Sub_8024554_Q_InstantlyKill_com ((void (*)()) 0x8024555)
#define EntityCollision ((int (*)(int, int)) 0x8026211)
#define Sub_8026A54_HIT_CLEAR_roulette ((void (*)()) 0x8026A55)
#define sub_8039E18 ((void (*)()) 0x8039E19)

// SRAM
#define ScEbufCounterInit (*(volatile unsigned char*) 0xE000E29)
#define ScEbufCounterRooms ((volatile unsigned char*) 0xE000E2A)

void FinalChanceWheelPatch() {
    // Vanilla code
    sub_8039E18();

    // Custom code
    if (CurrentRoomId == 13) {  // Special case for Keyzer room
        if (Switch2Flag == 1) {
            Sub_8026A54_HIT_CLEAR_roulette();
            EntityLeftOverStateList[64 * CurrentRoomId + CurrentEnemyData.CurEnemy_RoomEntitySlotId] = 2;
            Sub_8024554_Q_InstantlyKill_com();
        }
    } else {
        if (CurrentEnemyData.CurEnemy_padding == 16) { // Reset result bar
            ScEbufCounterRooms[CurrentRoomId] = 0;
            ScEbufCounter = ScEbufCounterInit + ScEbufCounterRooms[CurrentRoomId];
        }
    }
}
