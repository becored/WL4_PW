// @Description code will be excute once every frame, modified from UnlimitedRockBouncing
// @HookAddress 0x6C75E
// Mode: Thumb
// Made by Goldensunboy, ssp(shinespeciall)
// Modified by beco

/* Hook details
------------------------- this only works when the new function push lr at first and bx lr at last.
0x806C75E: LDR R0, 0x806C767    | 4803
0x806C760: MOV LR, R0           | 4686
0x806C762: LDR R0, pointer      | 4801
0x806C764: BX R0                | 4700
0x806C766: B 0x806C770          | E002
0x806C768: .fill a pointer      | 0XXXXXXX ; end with 1 (in binary) to make it run in thumb mode
0x806C76C: .fill 67C70608       | 0806C767 ; end with 1 (in binary) to make it run in thumb mode
0x806C770: nop                  | 46C0     ; i.e. mov r8, r8
0x806C772: nop....
-------------------------
Hook String:
@HookString 03 48 86 46 01 48 00 47 02 E0 P 67 C7 06 08 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46 C0 46
count:                                     ^14                                                                     ^38
Hook length: 38 Bytes
*/

struct EnemyDataStructure {
    unsigned short CurEnemy_usStatus;
    unsigned char pAnmData1;
    unsigned char pAnmData2;
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
    unsigned char CurEnemy_TWork0;
    unsigned char CurEnemy_TWork1;
    unsigned char CurEnemy_TWork2;
    unsigned char CurEnemy_TWork3;
    unsigned char CurEnemy_padding;
};

#define ENTITIES ((volatile struct EnemyDataStructure*) 0x3000104)
#define GameState (*(volatile unsigned char*) 0x3000C3C) // 03(restart current room) - ingame - 00(restart room) 01(fade) 02(game runtime) 03(lose level) 04(pause) 05(freeze) 06(lose level) 08(debug mode)

#define ucBossRoom (*(volatile unsigned char*) 0x300001B)
#define ucBgAnimatedStop (*(volatile unsigned char*) 0x3000046)
#define Sub_806E08C_BgAnimatedMain ((void (*)()) 0x806E08D)

#define PAL_RAM ((volatile unsigned char*) 0x5000000) // PAL RAM
#define VRAM 0x6000000 // VRAM
#define OBJ_MODE0_VRAM 0x6010000 // OBJ Character RAM

#define bWarioPalette ((volatile unsigned char*) 0x30030D0) // wario palettes, 2 lines

#define usAlpfaBLD1 (*(volatile unsigned char*) 0x300002A)
#define usAlpfaBLD2 (*(volatile unsigned char*) 0x300002B)
#define REG_DMA3SAD (*(volatile unsigned int*) 0x40000D4)
#define REG_DMA3DAD (*(volatile unsigned int*) 0x40000D8)
#define REG_DMA3CNT (*(volatile unsigned int*) 0x40000DC)

// Key control
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

#define ucGmScore_Tflg (*(volatile unsigned char*) 0x3000C02)
#define unk_8405AE8 0x8405AE8 // Score OBJ

// Misc function
#define sub_8001DA4_m4aSongNumStart ((void (*)(int)) 0x8001DA5)
#define sub_80766E8_TOptObjSet ((int (*)(int, int, char)) 0x80766E9)
#define Sub_806DAC0_TileEventIdTester ((int (*)(int,int)) 0x806dac1)
#define Sub_801EA3C_ChangeWarioReact_FIRE_Sub ((void (*)()) 0x801ea3d)
#define Sub_801EA64_ChangeWarioReact_Fat_Sub ((void (*)()) 0x801ea65)
#define Sub_801EB7C_ChangeWarioReact_Flat_Sub ((void (*)()) 0x801eb7d)
#define Sub_801EB04_ChangeWarioReact_Spring_Sub ((void (*)()) 0x801eb05)
#define Sub_801EB54_ChangeWarioReact_ICE_Sub ((void (*)()) 0x801eb55)
#define Sub_801EAB4_ChangeWarioReact_SNOW_Sub ((void (*)()) 0x801eab5)
#define Sub_801EA8C_ChangeWarioReact_ZOMBI_Sub ((void (*)()) 0x801ea8d)
#define Sub_801EADC_ChangeWarioReact_BALLOON_Sub ((void (*)()) 0x801eadd)
#define Sub_801EB2C_ChangeWarioReact_BAT_Sub ((void (*)()) 0x801eb2d)
#define Sub_801EBA4_ChangeWarioReact_Bubble_Sub ((void (*)()) 0x801eba5)

// Switch variables
#define Switch1Flag (*(volatile unsigned char*) 0x300002F)
#define Switch2Flag (*(volatile unsigned char*) 0x3000030)
#define Switch3Flag (*(volatile unsigned char*) 0x3000031)
#define Switch4Flag (*(volatile unsigned char*) 0x3000032)

// Misc variables
#define usRandomCount (*(volatile unsigned char*) 0x3000006)
#define ucSaveNum (*(volatile unsigned char*) 0x3000019)
#define WarioState (*(volatile unsigned char*) 0x3001898)
#define WarioAnimation (*(volatile unsigned char*) 0x3001899)
#define WarioXPos (*(volatile unsigned short*) 0x30018AA)
#define WarioYPos (*(volatile unsigned short*) 0x30018AC)
#define WarioInvincibility (*(volatile unsigned char*) 0x300189C)
#define usWarStopFlg (*(volatile unsigned short*) 0x30019F6)
#define uknown_counter (*(volatile unsigned char*) 0x30018A2)
#define word_30018CE (*(volatile unsigned short*) 0x30018CE)
#define word_30018CC (*(volatile unsigned short*) 0x30018CC)
#define Layer0_DecompressedDataPointer (*(volatile unsigned int*) 0x3000054)
#define CurrentTileset_EventIdTablePointer (*(volatile unsigned int*) 0x30031FC)
#define Layer0_Width (*(volatile unsigned short*) 0x3000058)
#define CurrentRoomHeader_Layer0MappingType (*(volatile unsigned char*) 0x3000075)
#define usTekiBgPosX (*(volatile unsigned short*) 0x300003A) // u16, usTekiBgPosX, Specify SCR position from enemy (BG0-PosX)
#define usBg0Hofs (*(volatile unsigned short*) 0x3001876) // layer 0 x offset, usBg0Hofs, short (used for non-synchronized layer 0)
#define usBg0Vofs (*(volatile unsigned short*) 0x3001878) // layer 0 y offset, usBg0Vofs, short (used for non-synchronized layer 0)
#define usBg1Hofs_CameraXPos (*(volatile unsigned short*) 0x300187A) // layer 1 x offset, usBg1Vofs, i.e. camera x position, short (realtime)
#define usBg1Vofs_CameraYPos (*(volatile unsigned short*) 0x300187C) // layer 1 y offset, usBg1Hofs, i.e. camera y position, short (realtime)
#define usBg2Hofs (*(volatile unsigned short*) 0x300187E) // layer 2 x offset, usBg2Vofs, short
#define usBg2Vofs (*(volatile unsigned short*) 0x3001880) // layer 2 y offset, usBg2Hofs, short
#define usBg3Hofs (*(volatile unsigned short*) 0x3001882) // layer 3 x offset, usBg2Vofs, short
#define usBg3Vofs (*(volatile unsigned short*) 0x3001884) // layer 3 y offset, usBg2Hofs, short
#define CameraXPos (*(volatile unsigned short*) 0x3003224)
#define CameraYPos (*(volatile unsigned short*) 0x3003226)

#define CurrentDifficulty (*(volatile unsigned char*) 0x03000017) // 00 for normal, =01 for hard, =02 for S-hard
#define CurrentPassage (*(volatile unsigned char*) 0x3000002) // 00(Entry) 01(Emerald) 02(Ruby) 03(Topaz) 04(Sapphire) 05(Golden) 06(Sound Room)
#define CurrentLevel (*(volatile unsigned char*) 0x3000003) // 00(first lvl) 01(second lvl) 02(third lvl) 03(fourth lvl) 04(Boss) 05(Mini-Game Shop)
#define CurrentRoom (*(volatile unsigned char*) 0x03000024)
#define KilledEnemiesCounter (*(volatile unsigned char*) 0x3000C06)
#define ucTimeUp (*(volatile unsigned char*) 0x3000047) // 01(fighting boss) 02(Losing coins) 03(Losing coins without coin counter) 04(hide coin counter) 10(fade to grayscale) 0f(no interaction between wario and enemies)

#define cGmStartFlg (*(volatile unsigned char*) 0x3000C3F)
#define cPauseFlag (*(volatile unsigned char*) 0x3000C35)
#define soft_reset (*(volatile unsigned char*) 0x300001E)
#define ADDR_KEY_4 (*(volatile unsigned short*) 0x3001848)

#define ScEbuf ((volatile unsigned char*) 0x3000B80) // 12 bytes
#define ScEbufCounter (*(volatile unsigned char*) 0x3000B86) // The Big Board counter
#define ScEbufYPos (*(volatile unsigned short*) 0x3000B88) // 2 bytes, default: 0x0210
#define ScEbufXPos (*(volatile unsigned short*) 0x3000B8A) // 2 bytes, default: 0x0040
#define Scbuf_ucAnmTimer (*(volatile unsigned char*) 0x3000BE1)
#define Scbuf_ucSeq (*(volatile unsigned char*) 0x3000BE3)
#define roulette_current_case_type (*(volatile unsigned short*) 0x3000C10)
#define roulette_moving_case_OAM_gfx (*(volatile unsigned short*) 0x3001470)

#define Pyaku1 (*(volatile unsigned short*) 0x30000A0)
#define Pyaku2 (*(volatile unsigned short*) 0x30000A1) // 01(in water) 00(else)

#define Enemy1State (*(volatile unsigned char*) 0x3000104)
#define Enemy1YPos (*(volatile unsigned short*) 0x300010C)
#define Enemy1XPos (*(volatile unsigned short*) 0x300010E)
#define Enemy2State (*(volatile unsigned char*) 0x3000130)
#define Enemy2YPos (*(volatile unsigned short*) 0x3000138)
#define Enemy2XPos (*(volatile unsigned short*) 0x300013A)

//#define word_30018B4 (*(volatile unsigned char*) 0x30031B4)
//#define unk_30031C8 (*(volatile unsigned short*) 0x30031C8) // Wario X move speed, used in Sub_800FE58_WarMoveConvX

// Boss variables
#define ucBossPause (*(volatile unsigned char*) 0x300001A)
#define CractusHp (*(volatile unsigned char*) 0x3000255) // Cractus's health
#define CatbatAnimationId (*(volatile unsigned char*) 0x3000120) // Catbat AnimationId
#define CatbatCuckooHp (*(volatile unsigned char*) 0x3000121) // Catbat's/Cuckoo Condor's health
#define CatbatPalette (*(volatile unsigned char*) 0x300011F) // Catbat's Palette (Default:0x00)
#define CatbatWaveType (*(volatile unsigned char*) 0x300014D) // Catbat's Wave Type (0x00:Straight‐line, 0x01:Wave, 0x11,Faster wave)
#define CatbatSharkBotYPos (*(volatile unsigned short*) 0x3000164) // Catbat's Shark Bot Y Position
#define CatbatSharkBotXPos (*(volatile unsigned short*) 0x3000166) // Catbat's Shark Bot X Position
#define CatbatSharkBotPalette (*(volatile unsigned char*) 0x3000177) // Catbat's Shark Bot Palette (Default:0x00)
#define CatbatSharkBotSpeed (*(volatile unsigned char*) 0x3000185) // Catbat's Shark Bot Speed (Default:0x01)

// My variables (perhaps unused in original)
// IRAM *Known issue: "Quit" doesn't save those variables
#define MiscValue1 (*(volatile unsigned short*) 0x3006F18)
#define MiscValue2 (*(volatile unsigned short*) 0x3006F1A)
// SRAM (0xE000E00~) *Will be removed in passage screen
#define KilledEnemiesCounterRooms ((volatile unsigned char*) 0xE000E00) // save A: 0x3006F00(Room00) - 0x3006F0F(Room15), save B: 0x3006F10(Room00) - 0x3006F1F(Room15)
//#define KilledEnemiesCounterTemp (*(volatile unsigned char*) 0xE000E20)
#define BossHpTemp (*(volatile unsigned char*) 0xE000E21)
#define Counter1 (*(volatile unsigned char*) 0xE000E22)
#define Counter2 (*(volatile unsigned char*) 0xE000E23)
#define usAlpfaBLDTemp1 (*(volatile unsigned char*) 0xE000E24)
#define usAlpfaBLDTemp2 (*(volatile unsigned char*) 0xE000E25)
#define MiscFlag1 (*(volatile unsigned char*) 0xE000E26)
#define MiscFlag2 (*(volatile unsigned char*) 0xE000E27)
#define high_diamond (*(volatile unsigned char*) 0xE000E28)
#define ScEbufCounterInit (*(volatile unsigned char*) 0xE000E29)
#define ScEbufCounterRooms ((volatile unsigned char*) 0xE000E2A)
#define CustomBlockFlag (*(volatile unsigned char*) 0xE000E2B)
// SRAM (0xE000F00~)
#define high_diamonds_sram ((volatile unsigned char*) 0xE000F00)

const unsigned char paletteBlack[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// Topaz 2 result bar data (don't forget to change destination address at: 0x39610, 0x396A0, 0x74F40)
const unsigned char resBarData[] = {00,05,05,05,05,05,05,00,04,06,07,07,06,04,00,04,05,03,04,06,05,04,02,04,03,06,02,00,07,06,04,07,06,07,04,07,04,06,07,06,00,04,03,05,07,03,05,04,03,05,07,03,05,00,03,04,05,03,04,06,00,04,05,04,04,07,04,00,07,07,07,07,07,07,00,07,07,07,07,07,07,00,03,07,04,07,04,05,00,03,04,06,05,03,04,04,03,06,05,05,04,00,06,04,07,05,04,03,07,05,04,07,06,02,00,06,05,04,03,04,07,00,07,04,05,06,07,04,05,06,07,05,04,01};
// Topaz 2 result bar X flag for each room (0: original, 1: 6, 2: 12)
const unsigned char resBarXflag[] = {1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 2};
// Topaz 2 result bar X position for each room (0x0040: original, 0x0100: 6, 0x0040: 12)
const unsigned short resBarXpos[] = {0x0040, 0x0100, 0x0040};

void FrameOperations() {
    // Vanilla code for animated tiles loading
    if ( (GameState == 2 || GameState == 6 || GameState == 4 && ucBossRoom == 1) && !ucBgAnimatedStop ) {
        Sub_806E08C_BgAnimatedMain();
    }

    // In-level Functions (inactive during pause)
    if (cGmStartFlg == 1 && cPauseFlag == 0 && ucBossPause == 0 && soft_reset == 0) {
        // Press L to trigger debug mode (Don't forget to remove before release!)
        /*
        if (ADDR_KEY_4 == KEY_L) {
            if (GameState == 8) {
                GameState = 2;
            }
            else if (GameState == 2) {
                GameState = 8;
            }
        }
        */

        // Boss room shenanigans
        /*
        // Emerald Passage - Boss Level - Boss Room (Cractus)
        if (CurrentPassage == 1 && CurrentLevel == 4 && CurrentRoom == 1) {
            // Initialize
            if (ucTimeUp == 0x00) {
                Counter1 = 3;
                Counter2 = 120;
                usAlpfaBLD1 = 0;
                usAlpfaBLD2 = 16;
                usAlpfaBLDTemp1 = usAlpfaBLD1;
                usAlpfaBLDTemp2 = usAlpfaBLD2;
            }
            // In-fight functions
            if (ucTimeUp == 0x01) {
                if (Switch1Flag == 0) {
                    Counter1 = 3;
                    if (CractusHp <= 5) {
                        Counter2 = 30;
                    } else if (CractusHp <= 10) {
                        Counter2 = 60;
                    } else {
                        Counter2 = 120;
                    }
                    usAlpfaBLDTemp1 = 0;
                    usAlpfaBLDTemp2 = 16;
                } else {
                    if (Counter2 <= 0) {
                        if (Counter1 <= 0) {
                            Switch1Flag = 3;
                            Counter1 = 3;
                            if (CractusHp <= 5) {
                                Counter2 = 30;
                            } else if (CractusHp <= 10) {
                                Counter2 = 60;
                            } else {
                                Counter2 = 120;
                            }
                            sub_8001DA4_m4aSongNumStart(216);
                        } else {
                            Counter1--;
                            if (CractusHp <= 5) {
                                Counter2 = 40;
                            } else if (CractusHp <= 10) {
                                Counter2 = 80;
                            } else {
                                Counter2 = 120;
                            }
                            usAlpfaBLDTemp1 = usAlpfaBLDTemp1 - 3;
                            usAlpfaBLDTemp2 = usAlpfaBLDTemp2 + 3;
                            usAlpfaBLD1 = usAlpfaBLDTemp1;
                            usAlpfaBLD2 = usAlpfaBLDTemp2;
                            sub_8001DA4_m4aSongNumStart(224);
                        }
                    } else {
                        if (Counter1 >= 3) {
                            if (usAlpfaBLDTemp1 < 16 && usAlpfaBLDTemp2 > 0) {
                                usAlpfaBLDTemp1 = usAlpfaBLDTemp1 + 4;
                                usAlpfaBLDTemp2 = usAlpfaBLDTemp2 - 4;
                                usAlpfaBLD1 = usAlpfaBLDTemp1;
                                usAlpfaBLD2 = usAlpfaBLDTemp2;
                            }
                        }
                        Counter2--;
                    }
                }
                BossHpTemp = CractusHp;
                }
                // Defeat boss functions
                if(ucTimeUp == 0x0B) {
                    Switch1Flag = 3; // Original bosses only use Switch#2 so it's okay to use others
                    //Switch3Flag = 1;
                }
            }
            // Ruby Passage - Boss Level - Boss Room (Cuckoo)
            if (CurrentPassage == 2 && CurrentLevel == 4 && CurrentRoom == 1) {
                // Initialize
                if (ucTimeUp == 0x00) {
                    Switch1Flag = 3;
                }
                // In-fight functions
                if (ucTimeUp == 0x01) {
                    // Damage functions
                    if(BossHpTemp != CatbatCuckooHp) {
                        if (Switch1Flag == 1) {
                            Switch1Flag = 3;
                            sub_8001DA4_m4aSongNumStart(215);
                        }
                        if (Switch1Flag == 0) {
                            Switch1Flag = 2;
                            sub_8001DA4_m4aSongNumStart(216);
                        }
                    }
                    BossHpTemp = CatbatCuckooHp;
                }
            }

            // Sapphire Passage - Boss Level - Boss Room (Catbat)
            if (CurrentPassage == 4 && CurrentLevel == 4 && CurrentRoom == 1) {
                // Initialize
                if (ucTimeUp == 0x00) {
                    Counter1 = 0; // Use as a flag
                    Counter2 = 90;
                }
                // In-fight functions
                if (ucTimeUp == 0x01) {
                    // Shark bot shenanigans
                    if (CatbatSharkBotSpeed != 0x08){
                        if (CatbatCuckooHp <= 6) {
                            CatbatSharkBotPalette = 0x08;
                            CatbatSharkBotSpeed = 12; // Set shark bot speed (Default:0x01)
                        } else if (CatbatCuckooHp <= 9) {
                            CatbatSharkBotPalette = 0x01;
                            CatbatSharkBotSpeed = 6; // Set shark bot speed (Default:0x01)
                        } else {
                            CatbatSharkBotSpeed = 3; // Set shark bot speed (Default:0x01)
                        }
                    }
                    // Damage functions
                    if(BossHpTemp != CatbatCuckooHp) {
                        if (CatbatCuckooHp == 6) {
                            //sub_8001DA4_m4aSongNumStart(748);
                            sub_80766E8_TOptObjSet(0x05F0, 0x0460, 0x44); // Generate smoke
                            sub_80766E8_TOptObjSet(0x05F0, 0x0560, 0x44); // Generate smoke
                            sub_80766E8_TOptObjSet(CatbatSharkBotYPos, CatbatSharkBotXPos, 0x07); // Generate splash
                            Switch3Flag = 2;
                        } else if (CatbatCuckooHp == 9) {
                            sub_80766E8_TOptObjSet(CatbatSharkBotYPos, CatbatSharkBotXPos, 0x07); // Generate splash
                        }
                    }
                    BossHpTemp = CatbatCuckooHp;
                    if (Counter1 == 1) {
                        if (Counter2 <= 0) {
                            if (CatbatAnimationId == 0x10) {
                                //CatbatAnimationId = 0x16;

                                if (CatbatCuckooHp <= 10) {
                                    CatbatWaveType = 0x11;
                                } else if (CatbatCuckooHp <= 5) {
                                    CatbatWaveType = 0x11;
                                }
                                Counter1 = 0;
                                Counter2 = 90;
                            }
                        } else {
                            Counter2--;
                        }
                    }
                    if (CatbatAnimationId == 0x11) {
                        Counter1 = 1;
                        Counter2 = 90;
                    }
                }
                // Defeat boss functions
                if (ucTimeUp == 0x0B) {
                    Switch3Flag = 3;
                }
            }
        */

        // Kill counter shenanigans
        /*
        if (KilledEnemiesCounterTemp != KilledEnemiesCounter) {
            int i = CurrentRoom;
            KilledEnemiesCounterRooms[i + (ucSaveNum * 16)] = KilledEnemiesCounterRooms[i + (ucSaveNum * 16)] + (KilledEnemiesCounter - KilledEnemiesCounterTemp);
        }
        KilledEnemiesCounterTemp = KilledEnemiesCounter;
        */

        // All difficulty
        // Emerald Passage - Level 1 - Room 12
        if (CurrentPassage == 1 && CurrentLevel == 0 && CurrentRoom == 12) {
            // Palette change
            REG_DMA3SAD = &paletteBlack;
            REG_DMA3DAD = (PAL_RAM + 0x000);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x020);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x200);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x220);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x240);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x260);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x2A0);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x300);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x320);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x340);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x360);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x380);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x3A0);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x3C0);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            REG_DMA3DAD = (PAL_RAM + 0x3E0);
            REG_DMA3CNT = 0x80000010;
            while (REG_DMA3CNT & 0x80000000) ;
            /*
            for (int i = 0; (0x00 + i) <= 0x3E; i++) {
                *(PAL_RAM + 0x00 + i) = 0;
            }
            for (int i = 0; (0x200 + i) <= 0x27E; i++) {
                *(PAL_RAM + 0x200 + i) = 0;
            }
            for (int i = 0; (0x2A0 + i) <= 0x2BE; i++) {
                *(PAL_RAM + 0x2A0 + i) = 0;
            }
            for (int i = 0; (0x300 + i) <= 0x3FE; i++) {
                *(PAL_RAM + 0x300 + i) = 0;
            }
            */
        }
        // Topaz Passage - Level 2
        if (CurrentPassage == 3 && CurrentLevel == 1) {
            int curBarXflag = resBarXflag[CurrentRoom];
            if (curBarXflag != 0) {
                ScEbufCounterInit = 0;
                for (int i = 0; i < CurrentRoom; i++) {
                    ScEbufCounterInit = ScEbufCounterInit + 1 + 6 * (resBarXflag[i]);
                }
                usTekiBgPosX = 0; // Fix Layer 0 X Offset
                if (CurrentRoom == 13) {
                    usTekiBgPosX = 0x20; // Special case for Keyzer room
                }
                if (GameState == 1) {
                    ScEbufCounter = ScEbufCounterInit + ScEbufCounterRooms[CurrentRoom];
                } else {
                    ScEbufCounterRooms[CurrentRoom] = ScEbufCounter - ScEbufCounterInit;
                    ScEbufXPos = resBarXpos[curBarXflag];
                    if (ScEbufCounter - ScEbufCounterInit > 0) {
                        ScEbufXPos = ScEbufXPos + 0x50 + (0x40 * (ScEbufCounter - ScEbufCounterInit - 1));
                    }
                    if (CurrentRoom == 13) {
                        ScEbufXPos -= 0x20; // Special case for Keyzer room
                        if (ScEbufCounter == 0x85) {
                            ScEbufXPos += 0x10;
                        }
                    }
                }
            }
        }
        // Golden Passage - Level 1 - Room 9
        if (CurrentPassage == 5 && CurrentLevel == 0 && CurrentRoom == 9) {
            if (WarioXPos <= 0x0040) {
                WarioXPos = 0x046F;
            } else if (WarioXPos >= 0x0470) {
                WarioXPos = 0x0041;
            }
            for (int c = 0 ; c < 24 ; c ++) {
                if (ENTITIES[c].CurEnemy_XPos <= 0x0040) {
                    ENTITIES[c].CurEnemy_XPos = 0x046F;
                } else if (ENTITIES[c].CurEnemy_XPos >= 0x0470) {
                    ENTITIES[c].CurEnemy_XPos = 0x0041;
                }
            }
        }

        // Normal
        if (CurrentDifficulty == 0) {
            // Entry Passage - Level 1 - Room 7
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 7) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[7 + (ucSaveNum * 16)] >= 1) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 8
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 8) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[8 + (ucSaveNum * 16)] >= 1) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 10
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 10) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[10 + (ucSaveNum * 16)] >= 1) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 14
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 14) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[14 + (ucSaveNum * 16)] >= 1) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Boss Level - Room 2
            if (CurrentPassage == 0 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 3 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Emerald Passage - Boss Level - Room 2
            if (CurrentPassage == 1 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 2 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Boss Level - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 2 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Sapphire Passage - Boss Level - Room 2
            if (CurrentPassage == 4 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 1 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Level 2 - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 2) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 4) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 11
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 11) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[11 + (ucSaveNum * 16)] >= 8) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 3 (Camera X:0x0080)
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 9 && CameraXPos == 0x0080) {
                if (Enemy1State == 1) {
                    MiscFlag1 = 0;
                    MiscValue1 = Enemy1YPos - 0x20;
                } else if (Enemy1State == 3) {
                    if (MiscFlag1 == 0) {
                        Enemy1YPos = Enemy1YPos + 2;
                        if (Enemy1YPos >= MiscValue1 + 120) {
                            MiscFlag1 = 1;
                        }
                    } else if (MiscFlag1 == 1) {
                        Enemy1YPos = Enemy1YPos - 2;
                        if (Enemy1YPos <= MiscValue1 - 120) {
                            MiscFlag1 = 0;
                        }
                    }
                }
                if (Enemy2State == 1) {
                    MiscFlag2 = 1;
                    MiscValue2 = Enemy2YPos - 0x20;
                } else if (Enemy2State == 3) {
                    if (MiscFlag2 == 0) {
                        Enemy2YPos = Enemy2YPos + 2;
                        if (Enemy2YPos >= MiscValue2 + 120) {
                            MiscFlag2 = 1;
                        }
                    } else if (MiscFlag2 == 1) {
                        Enemy2YPos = Enemy2YPos - 2;
                        if (Enemy2YPos <= MiscValue2 - 120) {
                            MiscFlag2 = 0;
                        }
                    }
                }
            }
            // Topaz Passage - Level 1 - Room 15
            if (CurrentPassage == 3 && CurrentLevel == 0 && CurrentRoom == 15) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[15 + (ucSaveNum * 16)] >= 1) {
                    Switch3Trigger();
                }
            }
            // Topaz Passage - Level 2 - Room 6
            if (CurrentPassage == 3 && CurrentLevel == 1 && CurrentRoom == 6) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[6 + (ucSaveNum * 16)] >= 4) {
                    Switch3Trigger();
                }
            }
        }
        // Hard
        if (CurrentDifficulty == 1) {
            // Entry Passage - Level 1 - Room 7
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 7) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[7 + (ucSaveNum * 16)] >= 2) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 8
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 8) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[8 + (ucSaveNum * 16)] >= 2) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 10
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 10) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[10 + (ucSaveNum * 16)] >= 2) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 14
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 14) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[14 + (ucSaveNum * 16)] >= 2) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Boss Level - Room 2
            if (CurrentPassage == 0 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 3 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Emerald Passage - Boss Level - Room 2
            if (CurrentPassage == 1 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 5 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Boss Level - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 3 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Sapphire Passage - Boss Level - Room 2
            if (CurrentPassage == 4 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 2 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Level 2 - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 2) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 6) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 11
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 11) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[11 + (ucSaveNum * 16)] >= 8) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 3 (Camera X:0x0080)
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 9 && CameraXPos == 0x0080) {
                if (Enemy1State == 1) {
                    MiscFlag1 = 0;
                    MiscValue1 = Enemy1YPos - 0x20;
                } else if (Enemy1State == 3) {
                    if (MiscFlag1 == 0) {
                        Enemy1YPos = Enemy1YPos + 3;
                        if (Enemy1YPos >= MiscValue1 + 120) {
                            MiscFlag1 = 1;
                        }
                    } else if (MiscFlag1 == 1) {
                        Enemy1YPos = Enemy1YPos - 3;
                        if (Enemy1YPos <= MiscValue1 - 120) {
                            MiscFlag1 = 0;
                        }
                    }
                }
                if (Enemy2State == 1) {
                    MiscFlag2 = 1;
                    MiscValue2 = Enemy2YPos - 0x20;
                } else if (Enemy2State == 3) {
                    if (MiscFlag2 == 0) {
                        Enemy2YPos = Enemy2YPos + 3;
                        if (Enemy2YPos >= MiscValue2 + 120) {
                            MiscFlag2 = 1;
                        }
                    } else if (MiscFlag2 == 1) {
                        Enemy2YPos = Enemy2YPos - 3;
                        if (Enemy2YPos <= MiscValue2 - 120) {
                            MiscFlag2 = 0;
                        }
                    }
                }
            }
            // Topaz Passage - Level 1 - Room 15
            if (CurrentPassage == 3 && CurrentLevel == 0 && CurrentRoom == 15) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[15 + (ucSaveNum * 16)] >= 2) {
                    Switch3Trigger();
                }
            }
            // Topaz Passage - Level 2 - Room 6
            if (CurrentPassage == 3 && CurrentLevel == 1 && CurrentRoom == 6) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[6 + (ucSaveNum * 16)] >= 6) {
                    Switch3Trigger();
                }
            }
        }
        // S-Hard
        if (CurrentDifficulty == 2) {
            // Entry Passage - Level 1 - Room 7
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 7) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[7 + (ucSaveNum * 16)] >= 3) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 8
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 8) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[8 + (ucSaveNum * 16)] >= 3) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 10
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 10) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[10 + (ucSaveNum * 16)] >= 3) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Level 1 - Room 14
            if (CurrentPassage == 0 && CurrentLevel == 0 && CurrentRoom == 14) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[14 + (ucSaveNum * 16)] >= 3) {
                    Switch3Trigger();
                }
            }
            // Entry Passage - Boss Level - Room 2
            if (CurrentPassage == 0 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 5 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Emerald Passage - Boss Level - Room 2
            if (CurrentPassage == 1 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 8 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Boss Level - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 4 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Sapphire Passage - Boss Level - Room 2
            if (CurrentPassage == 4 && CurrentLevel == 4 && CurrentRoom == 2 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 3 && Switch4Flag == 0) {
                Switch4Trigger();
            }
            // Ruby Passage - Level 2 - Room 2
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 2) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[2 + (ucSaveNum * 16)] >= 9) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 11
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 11) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[11 + (ucSaveNum * 16)] >= 8) {
                    Switch3Trigger();
                }
            }
            // Ruby Passage - Level 2 - Room 3 (Camera X:0x0080)
            if (CurrentPassage == 2 && CurrentLevel == 1 && CurrentRoom == 9 && CameraXPos == 0x0080) {
                if (Enemy1State == 1) {
                    MiscFlag1 = 0;
                    MiscValue1 = Enemy1YPos - 0x20;
                } else if (Enemy1State == 3) {
                    if (MiscFlag1 == 0) {
                        Enemy1YPos = Enemy1YPos + 4;
                        if (Enemy1YPos >= MiscValue1 + 120) {
                            MiscFlag1 = 1;
                        }
                    } else if (MiscFlag1 == 1) {
                        Enemy1YPos = Enemy1YPos - 4;
                        if (Enemy1YPos <= MiscValue1 - 120) {
                            MiscFlag1 = 0;
                        }
                    }
                }
                if (Enemy2State == 1) {
                    MiscFlag2 = 1;
                    MiscValue2 = Enemy2YPos - 0x20;
                } else if (Enemy2State == 3) {
                    if (MiscFlag2 == 0) {
                        Enemy2YPos = Enemy2YPos + 4;
                        if (Enemy2YPos >= MiscValue2 + 120) {
                            MiscFlag2 = 1;
                        }
                    } else if (MiscFlag2 == 1) {
                        Enemy2YPos = Enemy2YPos - 4;
                        if (Enemy2YPos <= MiscValue2 - 120) {
                            MiscFlag2 = 0;
                        }
                    }
                }
            }
            // Topaz Passage - Level 1 - Room 15
            if (CurrentPassage == 3 && CurrentLevel == 0 && CurrentRoom == 15) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[15 + (ucSaveNum * 16)] >= 3) {
                    Switch3Trigger();
                }
            }
            // Topaz Passage - Level 2 - Room 6
            if (CurrentPassage == 3 && CurrentLevel == 1 && CurrentRoom == 6) {
                if (GameState == 1 && Switch3Flag == 1) {
                    Switch3Flag = 3;
                }
                if (Switch3Flag == 0 && KilledEnemiesCounterRooms[6 + (ucSaveNum * 16)] >= 8) {
                    Switch3Trigger();
                }
            }
        }
    }
}

void Switch3Trigger() {
    Switch3Flag = 2; // Set 2 instead of 1 so that will trigger animation
    sub_8001DA4_m4aSongNumStart(235);
}

void Switch4Trigger() {
    Switch4Flag = 2; // Set 2 instead of 1 so that will trigger animation
    sub_8001DA4_m4aSongNumStart(235);
}
