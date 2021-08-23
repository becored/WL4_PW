// @Description Rewritten_Sub_8057248_EntityAI_0x6A_Tmain_zako_kiyobu
// @HookAddress 0x78E9A8
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
    unsigned char CurEnemy_CurrentAnimationId;
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
#define AlphaBld_EVB_target (*(volatile unsigned char*) 0x30000D8)
#define CurrentEnemyData (*(volatile struct ENEMY_DATA*) 0x3000A24)

// Subroutine
#define Sub_8057248_EntityAI_0x6A_Tmain_zako_kiyobu ((void (*)()) 0x8057249)

void Rewritten_Sub_8057248_EntityAI_0x6A_Tmain_zako_kiyobu() {
    // Custom code
    if (CurrentEnemyData.CurEnemy_CurrentAnimationId != 110 && AlphaBld_EVB_target != 0) {
        CurrentEnemyData.CurEnemy_CurrentAnimationId = 110;
    }

    // Vanilla code
    Sub_8057248_EntityAI_0x6A_Tmain_zako_kiyobu();
}
