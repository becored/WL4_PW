// @Description BoardReactSubPatch
// @HookAddress 0x39552
// @HookString 02 48 86 46 02 48 00 47 00 00 A7 95 03 08 P
// Mode: Thumb
// Made by beco, referenced Blanchon's FrameOperationWithRouletteEdit.c

/* Patch & Hook details
.thumb
    .dcb 1
    ldr r0, .DATA
    mov lr, r0
    ldr r0, .DATA + 4
    bx r0
    .dcb 1
.DATA:
    .word 0x080395A7
    .word 0xAAAAAAAA
 */

#define CurrentRoomId (*(volatile unsigned char*) 0x03000024)

#define ChangeWarioReact_FIRE_Sub ((void (*)()) 0x801EA3D)
#define ChangeWarioReact_Fat_Sub ((void (*)()) 0x801EA65)
#define ChangeWarioReact_Flat_Sub ((void (*)()) 0x801EB7D)
#define ChangeWarioReact_Spring_Sub ((void (*)()) 0x801EB05)
#define ChangeWarioReact_ICE_Sub ((void (*)()) 0x801EB55)
#define ChangeWarioReact_SNOW_Sub ((void (*)()) 0x801EAB5)
#define ChangeWarioReact_ZOMBI_Sub ((void (*)()) 0x801EA8D)
#define ChangeWarioReact_BALLOON_Sub ((void (*)()) 0x801EADD)
#define ChangeWarioReact_BAT_Sub ((void (*)()) 0x801EB2D)
#define ChangeWarioReact_Bubble_Sub ((void (*)()) 0x801EBA5)

void BoardReactSubPatch() {
    switch ( CurrentRoomId ) {
        case 1:
            ChangeWarioReact_SNOW_Sub();
            break;
        case 3:
            ChangeWarioReact_Fat_Sub();
            break;
        case 4:
            ChangeWarioReact_FIRE_Sub();
            break;
        case 6:
            ChangeWarioReact_Fat_Sub();
            break;
        case 7:
            ChangeWarioReact_ZOMBI_Sub();
            break;
        case 8:
            ChangeWarioReact_Spring_Sub();
            break;
        case 9:
            ChangeWarioReact_Spring_Sub();
            break;
        case 11:
            ChangeWarioReact_ICE_Sub();
            break;
        case 12:
            ChangeWarioReact_Fat_Sub();
            break;
        case 13:
            ChangeWarioReact_ICE_Sub();
            break;
        default:
            return;
    }
}
