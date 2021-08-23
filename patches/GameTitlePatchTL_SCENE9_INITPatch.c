// @Description GameTitlePatchTL_SCENE9_INITPatch
// @HookAddress 0x3766
// @HookString 02 48 86 46 02 48 00 47 00 00 07 39 00 08 P
// Mode: Thumb
// Made by beco

#define Sub_800B280_GetEndingType ((void (*)()) 0x800B281)
#define Sub_8003BF0_Init__Push_Start ((void (*)()) 0x8003BF1)
#define Sub_8003A18_Initialize_GameStartCutsceneControl ((void (*)(int)) 0x8003A19)

#define usEndingType (*(volatile unsigned char*) 0x3002C84)

void GameTitlePatchTL_SCENE9_INITPatch() {
    // Vanilla code
    Sub_800B280_GetEndingType();

    // Custom code
    if (usEndingType == 2) {
        usEndingType = 3;
    } else if (usEndingType == 3) {
        usEndingType = 2;
    }

    // Vanilla code
    Sub_8003BF0_Init__Push_Start();
    Sub_8003A18_Initialize_GameStartCutsceneControl(26);
}
