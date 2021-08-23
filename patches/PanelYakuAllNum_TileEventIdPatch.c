// @Description Rewritten TileEventIDTester (Sub_806DAC0_PanelYakuAllNum_TileEventWork) in C. You can use it as a base to create custom blocks for example, though it will require additional work on this function and other parts of WL4 rom.
// @HookAddress 0x6daca
// @HookString 024a 9646024a 10470000 37dd0608 P

/* Patch & Hook details

	.thumb
    .dcb 1
    ldr r2, .DATA
    mov lr, r2
    ldr r2, .DATA + 4
    bx r2
    .dcb 1
  .DATA:
    .word 0x0806DD37
    .word 0xAAAAAAAA

 */

// Made by Blanchon with the assistance of ssp (helped a lot with debugging, simplified the hook & code, gave advices, etc) and Goldensunboy.

// RAM addresses used by TileEventIDTester (Sub_806DAC0_PanelYakuAllNum_TileEventWork)

#define CurrentTileset_EventIdTablePointer (*(volatile unsigned int*) 0x30031FC)
#define CurrentRoomHeader_TilesetId (*(volatile unsigned char*) 0x3000074)

#define CurrentRoomHeader_Layer0MappingType (*(volatile unsigned char*) 0x3000075)
#define CurrentRoomHeader_Layer1MappingType (*(volatile unsigned char*) 0x3000076)
#define CurrentRoomHeader_Layer2MappingType (*(volatile unsigned char*) 0x3000077)
#define CurrentRoomHeader_Layer3MappingType (*(volatile unsigned char*) 0x3000078)

#define CurrentRoomHeader_LayerPriorityALphaParam (*(volatile unsigned char*) 0x300008e)

#define Layer0_DecompressedDataPointer (*(volatile unsigned int*) 0x3000054)
#define Layer0_Width (*(volatile unsigned short*) 0x3000058)
#define Layer0_Height (*(volatile unsigned short*) 0x300005a)

#define Layer1_DecompressedDataPointer (*(volatile unsigned int*) 0x300005c)
#define Layer1_Width (*(volatile unsigned short*) 0x3000060)
#define Layer1_Height (*(volatile unsigned short*) 0x3000062)

#define Layer2_DecompressedDataPointer (*(volatile unsigned int*) 0x3000064)
#define Layer2_Width (*(volatile unsigned short*) 0x3000068)
#define Layer2_Height (*(volatile unsigned short*) 0x300006a)

#define MapSwitch1 (*(volatile unsigned char*) 0x300002f)
#define MapSwitch4 (*(volatile unsigned char*) 0x3000032) // frog blocks, etc (see WL4 RAM record)

#define Terrain_usField (*(volatile unsigned short*) 0x30000a0)
#define Terrain_usKoka_SolidOrWater (*(volatile unsigned short*) 0x30000a2) // 030000a2 : u16 Pyaku[1] - usKoka - 01(in water) 00(else) (from WL4 RAM record)

// Various RAM addresses for potential custom code (add what you need)

#define CurrentLevel (*(volatile unsigned char*) 0x3000003)
#define CurrentRoom (*(volatile unsigned char*) 0x3000024)
#define ucTimeUp (*(volatile unsigned char*) 0x3000047) // 01(fighting boss) 02(Losing coins) 03(Losing coins without coin counter) 04(hide coin counter) 10(fade to grayscale) 0f(no interaction between wario and enemies)

#define WarioState (*(volatile unsigned char*) 0x3001898)
#define WarioAnimation (*(volatile unsigned char*) 0x3001899)
#define WarioInvincibility (*(volatile unsigned char*) 0x300189C)
#define WarioOrientation (*(volatile unsigned char*) 0x30018A6)
#define WarioCurrentEnvironment (*(volatile unsigned char*) 0x30018B2)

#define ChangeWarioReact_FIRE_Sub ((void (*)()) 0x801ea3d)
#define ChangeWarioReact_Fat_Sub ((void (*)()) 0x801ea65)
#define ChangeWarioReact_Flat_Sub ((void (*)()) 0x801eb7d)
#define ChangeWarioReact_Spring_Sub ((void (*)()) 0x801eb05)
#define ChangeWarioReact_ICE_Sub ((void (*)()) 0x801eb55)
#define ChangeWarioReact_SNOW_Sub ((void (*)()) 0x801eab5)
#define ChangeWarioReact_ZOMBI_Sub ((void (*)()) 0x801ea8d)
#define ChangeWarioReact_BALLOON_Sub ((void (*)()) 0x801eadd)
#define ChangeWarioReact_BAT_Sub ((void (*)()) 0x801eb2d)
#define ChangeWarioReact_Bubble_Sub ((void (*)()) 0x801eba5)

// My variables (perhaps unused in original)
// SRAM (0xE000E00~) *Will be removed in passage screen
#define CustomBlockFlag (*(volatile unsigned char*) 0xE000E2B)

int PanelYakuAllNum_TileEventIdPatch(unsigned short Y_value, unsigned short X_Value)
{
  unsigned short a;

  unsigned char v11; // EventID for tiles in layer 0
  unsigned char v12; // "       "      "   " layer 1
  unsigned char v13; // "       "      "   " layer 2

  unsigned short v7;
  unsigned short v10;

  // 3 local vars for calculus
  unsigned int i ;
  unsigned int j ;
  unsigned char k ;

  i = 0 ;
  j = 0 ;
  k = 0 ;

  v12 = 0 ;
  v13 = 0 ;
  v11 = 0 ;

  Terrain_usField = 0;
  Terrain_usKoka_SolidOrWater = 0;

  if ( Y_value >= Layer1_Height << 6 || X_Value >= Layer1_Width << 6 )
  {
    return 0;
  }


  int v3;
  int v4;
  int v5;
  int v6;

  int v8;
  int v9;


  volatile unsigned int *p ;
  volatile unsigned char *q ;

	// Layer 1 tile detection

  i = ((Y_value << 16) >> 22) ;
  i = i * Layer1_Width ;
  i = i + ((X_Value << 16) >> 22) ;
  i = i << 1 ;
  i = i + Layer1_DecompressedDataPointer ;

  p = i ;

  j = *p ;
  a = j ; // converting int value to short, as the original function does with a LDRH ; a is an unsigned short value
  j = a ;

  j = j << 1 ;
  j = j + CurrentTileset_EventIdTablePointer ;

  q = j;

  k = *q;
  a = k;
  k = a;
  v12 = k;

  // Layer 2 tile detection

  i = ((Y_value << 16) >> 22);
  i = i * Layer2_Width;
  i = i + ((X_Value << 16) >> 22);
  i = i << 1;
  i = i + Layer2_DecompressedDataPointer;

  p = i;

  j = *p;
  a = j;
  j = a;

  j = j << 1 ;
  j = j + CurrentTileset_EventIdTablePointer;

  q = j;

  k = *q;
  a = k;
  k = a;

  v13 = k;

  v7 = 0 ;
  v10 = 0 ;

  unsigned int c ;

// There are 0x100 (256 in decimal) different EventIDs available in WL4. Last case is 0xff, 255.
// A bunch of vanilla blocks are grouped in conditions after switch cases.

  switch ( v12 ) // cases for Layer 1 tiles
  {
	  // custom cases

	  case 176: // 0xB0
      if (CustomBlockFlag == 0) {
          if (MapSwitch1 == 0) {
              v7 = 5;
          } else if (MapSwitch1 == 1) {
              v7 = 6;
          }
      }
  	  goto LABEL_49;

  	 case 177: // 0xB1
     if (CustomBlockFlag == 0) {
         if (MapSwitch1 == 1) {
             v7 = 5;
         } else if (MapSwitch1 == 0) {
             v7 = 6;
         }
     }
  	 goto LABEL_49;

    // vanilla cases
    case 106:
      v7 = 5;
      goto LABEL_49;
    case 107:
      v7 = 6;
      goto LABEL_49;
    case 104: // 0x68 Slippery ice platforms
      goto LABEL_33;
    case 4: // left part of downpipe
      v7 = 7;
      goto LABEL_49;
    case 5: // right part of downpipe
      v7 = 8;
      goto LABEL_49;
    case 6: // left part of upperpipe
      v7 = 9;
      goto LABEL_49;
    case 7: // right part of upperpipe
      v7 = 10;
      goto LABEL_49;
    case 121: // ladders
LABEL_29:
      v7 = 2;
      goto LABEL_49;
    case 123:
LABEL_31:
      v7 = 4;
      goto LABEL_49;
    case 2:
      goto LABEL_42;
    case 122: // top of ladders (can walk on)
      goto LABEL_35;
  }

  unsigned char B ;

  c = v12 - 0x59 ;

  if ( c <= 4 ) // EventID 0x59-5D
  {
   v7 = 11; // slippery ice effect
  }

  if ( v7 || CurrentRoomHeader_Layer2MappingType != 16 )
    goto LABEL_49;

  switch ( v13 ) // cases for Layer 2 tiles
  {
    case 2:
LABEL_42:
      v7 = 1;
      goto LABEL_49;
    case 121:
      goto LABEL_29;
    case 123:
      goto LABEL_31;
    case 104:
LABEL_33:
      v7 = 11; // slippery ice effect
      goto LABEL_49;
    case 122:
LABEL_35:
      v7 = 3;
      goto LABEL_49;
  }

  c = v13 - 0x38 ;
  if ( c > 7 ) // ID > 0x3f or ID < 0x38
  {
	  c = v13 - 0x98 ;
    if ( c <= 3 ) // EventID from 0x98 to 0x9b
    {
      v8 = v13 - 0x98;
      if ( MapSwitch1 & 1 )
      {
        if ( v8 > 1 )
          v7 = ((v13 + 0x68) & 1) + 2;
      }
      else if ( v8 <= 1 )
      {
        v7 = v13 - 0x96;
      }
    }
    goto LABEL_49;
  }

  c = v13 - 0x37 ;

  	  unsigned int *P ;
  if ( c > 3 ) // if ID > 0x3a or ID < 0x37
  {
	  c = (v13 + 0x2FFFFF3);
	  P = c;
	  c = (*P - 1) & 0xffu;
    if ( c > 1 )
      goto LABEL_49;

    goto LABEL_42;
  }
   c = (v13 + 0x2FFFFF7);
	  P = c;
	  B = *P; // B like LDRB (load register BYTE), the thing ida pro's pseudocode didn't notice lol, so patch would load an int when it's a byte. In this case loading an int from RAM addresses can get you unwanted digits (so far greater numbers) that fails the condition, for example looking into debugger I saw it was loading 0x10000 when it's just 0 in reality ...
  if ( !B || B == 3 )
    goto LABEL_42;

LABEL_49:

  Terrain_usField = v7;
  v9 = 0;
  v10 = 0;


 c = v7 ;
 c = c << 16 ;

  if ( CurrentRoomHeader_LayerPriorityALphaParam > 7u
    && CurrentRoomHeader_Layer0MappingType <= 0x10u )
  {
    if ( CurrentRoomHeader_Layer0MappingType )
    {
      if ( Y_value >= Layer0_Height << 6 || X_Value >= Layer0_Width << 6 )
      {
          return Terrain_usField << 16;
      }

      // Layer 0 tile detection

      i = ((Y_value << 16) >> 22) ;
      i = i * Layer0_Width ;
      i = i + ((X_Value << 16) >> 22) ;
      i = i << 1 ;
      i = i + Layer0_DecompressedDataPointer ;

      p = i ;

      j = *p ;
      a = j ;
      j = a ;

      j = j << 1 ;
      j = j + CurrentTileset_EventIdTablePointer ;

      q = j;

      k = *q ;
      a = k ;
      k = a ;

      v11 = k ;


      c = v11 - 0x4c;
	    if ( c <= 0xC) // if tile in layer 0 is water or currents
      {
        v9 = 1;
        switch ( v11 ) // cases for Layer 0 tiles
        {
          case 81:
            v10 = 12;
            break;
          case 82:
            v10 = 13;
            break;
          case 83:
            v10 = 14;
            break;
          case 84:
            v10 = 15;
            break;
          case 85:
            v10 = 16;
            break;
          case 86:
            v10 = 17;
            break;
          case 87:
            v10 = 18;
            break;
          case 88:
            v10 = 19;
            break;
        }
        {
        if ( !(MapSwitch4 & 1) ) // if frog switch isn't pressed yet
          switch ( v11 )
          {
            case 76:
              v10 = 12;
              break;
            case 77:
              v10 = 17;
              break;
            case 78:
              v10 = 18;
              break;
            case 79:
              v10 = 19;
              break;
          }
        }
      }
    }
  }

  else if ((v12 - 0x4C) <= 0xC && (v12 - 0x4C) >= 0 )
  {
    v9 = 1;
  }

  if ( v9 == 1 && (v10 || Terrain_usField != 1) )
  {
    Terrain_usField = v10;
  }
  Terrain_usKoka_SolidOrWater = v9;

  return (Terrain_usField << 16) | v9;
}
