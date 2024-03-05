#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_def.h"
#include "sound_set_map.h"
#include <stdint.h>
#endif
#include <string.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define CS_WEAPONS_ALL_NMBR 12
#define CS_NONWEAPON_ITEMS_NMBR 3
#define GGT_CONGRAT_NMBR 12

static const tImage **gpListOfImages[23] = {&IMG_weapon, &IMG_trophy, &IMG_target, &IMG_steps, &IMG_shield_big, &IMG_shield, &IMG_pistol_small, &IMG_medaile, &IMG_aim, &IMG_ak47, &IMG_ak47_small_2, &IMG_ammo, &IMG_arrows, &IMG_bomb, &IMG_bomb_small, &IMG_defuse, &IMG_flash, &IMG_flash_big, &IMG_heart, &IMG_heart_big, &IMG_invisibility_big, &IMG_machinegun_big, &IMG_machinegun_small};
static const tImage **gpOrbImage[4] = {&IMG_machinegun_big, &IMG_shield_big, &IMG_flash_big, &IMG_healing_big};
static const uint8_t *gpOrbName[4] = {"MACHINEGUN", "ARMOR", "SNIPER", "HEALING"};
static const tImage **gpWeaponsList[CS_WEAPONS_ALL_NMBR] = {&IMG_knife, &IMG_usp, &IMG_pistol_small, &IMG_Deagle, &IMG_mp5, &IMG_P90, &IMG_m4, &IMG_ak47_small_2, &IMG_Aug, &IMG_sg552, &IMG_awp, &IMG_tactical_shield}; // 10 weapons, knife, kevlar, IMG_ammo, IMG_defuse
static const uint8_t *gpWeaponsNameList[CS_WEAPONS_ALL_NMBR] = {
    "Knife",
    "USP",
    "Glock",
    "Deagle",
    "MP5",
    "P90",
    "M4",
    "AK47",
    "AUG",
    "SG552",
    "AWP",
    "Shield"};
static const tImage **gpItemList[CS_WEAPONS_ALL_NMBR + CS_NONWEAPON_ITEMS_NMBR] = {&IMG_knife, &IMG_usp, &IMG_pistol_small, &IMG_Deagle, &IMG_mp5, &IMG_P90, &IMG_m4, &IMG_ak47_small_2, &IMG_Aug, &IMG_sg552, &IMG_awp, &IMG_tactical_shield, &IMG_ammo, &IMG_Kevlar2, &IMG_defuse}; // 10 weapons, knife, kevlar, IMG_ammo, IMG_defuse
static const uint8_t *gpItemNameList[CS_WEAPONS_ALL_NMBR + CS_NONWEAPON_ITEMS_NMBR] = {
    "Knife",
    "USP",
    "Glock",
    "Deagle",
    "MP5",
    "P90",
    "M4",
    "AK47",
    "AUG",
    "SG552",
    "AWP",
    "Shield",
    "Ammo",
    "Kevlar",
    "DefKit",
};

static const uint8_t *gpCongratulationsList[GGT_CONGRAT_NMBR] = {
    "Congrats",
    "Good job",
    "Well done",
    "Nice",
    "You're good",
    "Hoooray",
    "Kudos",
    "Bravo",
    "Excellent",
    "Way to go",
    "Phenomenal",
    "Splendid"};

/*int8_t circle_16_2[92][2] = {
    {-12, -11},
    {-12, -10},
    {-13, -9},
    {-14, -8},
    {-14, -7},
    {-15, -6},
    {-15, -5},
    {-15, -4},
    {-16, -3},
    {-16, -2},
    {-16, -1},
    {-16, 0},
    {-16, 1},
    {-16, 2},
    {-16, 3},
    {-15, 4},
    {-15, 5},
    {-15, 6},
    {-14, 7},
    {-14, 8},
    {-13, 9},
    {-12, 10},
    {-12, 11},
    {-11, 12},
    {-10, 12},
    {-9, 13},
    {-8, 14},
    {-7, 14},
    {-6, 15},
    {-5, 15},
    {-4, 15},
    {-3, 16},
    {-2, 16},
    {-1, 16},
    {0, 16},
    {1, 16},
    {2, 16},
    {3, 16},
    {4, 15},
    {5, 15},
    {6, 15},
    {7, 14},
    {8, 14},
    {9, 13},
    {10, 12},
    {11, 12},
    {12, 11},
    {12, 10},
    {13, 9},
    {14, 8},
    {14, 7},
    {15, 6},
    {15, 5},
    {15, 4},
    {16, 3},
    {16, 2},
    {16, 1},
    {16, 0},
    {16, -1},
    {16, -2},
    {16, -3},
    {15, -4},
    {15, -5},
    {15, -6},
    {14, -7},
    {14, -8},
    {13, -9},
    {12, -10},
    {12, -11},
    {11, -12},
    {10, -12},
    {9, -13},
    {8, -14},
    {7, -14},
    {6, -15},
    {5, -15},
    {4, -15},
    {3, -16},
    {2, -16},
    {1, -16},
    {0, -16},
    {-1, -16},
    {-2, -16},
    {-3, -16},
    {-4, -15},
    {-5, -15},
    {-6, -15},
    {-7, -14},
    {-8, -14},
    {-9, -13},
    {-10, -12},
    {-11, -12}};*/

typedef enum {
    teamCT = 0,
    teamTerr = 1,
    teamNone = 255
} teamType;

volatile static tImage **gvpWeaponsAllList[CS_WEAPONS_ALL_NMBR] = {&IMG_knife, &IMG_usp, &IMG_pistol_small, &IMG_Deagle, &IMG_mp5, &IMG_P90, &IMG_m4, &IMG_ak47_small_2, &IMG_Aug, &IMG_sg552, &IMG_awp, &IMG_tactical_shield}; // 10 weapons + knife + shield

void DISPLAY_drawBitmap(uint8_t aX, uint8_t aY, uint16_t aBitmapIndex) {
    ENGINE_drawBitmapByIndex(aX, aY, aBitmapIndex);
    // ENGINE_drawBitmapByIndex(aX, aY, ak47Index);
}

void DISPLAY_initLayout(uint8_t aNumberOfCells) {
    if (aNumberOfCells == 0 || aNumberOfCells > 6) {
        return;
    } else {

        switch (aNumberOfCells) {
        case 1: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT - 2, 1);
        } break;
        case 2: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(0, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2 - 3, 1);
        } break;
        case 3: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 1, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 2, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(0, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2 - 3, 1);
        } break;
        case 4: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 1, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 2, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(0, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 1, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 2, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
        } break;
        case 5: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 1, 0, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 2, 1, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(0, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 1, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH / 2 - 1, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 + 2, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH / 2 - 3, DISPLAY_HEIGHT / 2 - 3, 1);

            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 - 13, DISPLAY_HEIGHT / 2 - 13, 26, 26, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 - 12, DISPLAY_HEIGHT / 2 - 12, 24, 24, 1);
            ENGINE_fillRectangle(DISPLAY_WIDTH / 2 - 11, DISPLAY_HEIGHT / 2 - 11, 22, 22, 0);
        } break;
        case 6: {
            ENGINE_drawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, 1, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2 - 3, 1);
            ENGINE_drawRectangle(0, DISPLAY_HEIGHT / 2 + 1, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - 1, 1);
            ENGINE_drawRectangle(1, DISPLAY_HEIGHT / 2 + 2, DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2 - 3, 1);

            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 - 13, DISPLAY_HEIGHT / 2 - 12, 26, 24, 1);
            ENGINE_drawRectangle(DISPLAY_WIDTH / 2 - 12, DISPLAY_HEIGHT / 2 - 11, 24, 22, 1);
            ENGINE_fillRectangle(DISPLAY_WIDTH / 2 - 11, DISPLAY_HEIGHT / 2 - 10, 22, 20, 0);
        } break;

        default:
            break;
        }
    }
}

void DISPLAY_rank(uint8_t aX, uint8_t aY, uint8_t aCell) {
    uint8_t lRank = ENGINE_getRank();
    if (aCell == 1) {
        ENGINE_drawBitmapByIndex(aX, aY, EII_MEDAILE);
        ENGINE_fillRectangle(aX + IMG_medaile->width + 10, aY + 7, 22, 14, 0); // clean space for rank number
        ENGINE_drawInt(aX + IMG_medaile->width + 10 + 11, aY + 7, lRank, 'C', 1);
    } else if (aCell == 5) {
        ENGINE_fillRectangle(aX - 11, aY - 7, 22, 14, 0); // clean space for rank number
        ENGINE_drawInt(aX, aY - 7, lRank, 'C', 1);
    }
}

void DISPLAY_playersCount(uint8_t aX, uint8_t aY, uint8_t aCount) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_STICKMAN);
    ENGINE_fillRectangle(aX + IMG_stickman->width + 10, aY, 22, 14, 0); // clean space for count number
    ENGINE_drawInt(aX + IMG_stickman->width + 10 + 11, aY, aCount, 'C', 1);
}

void DISPLAY_playersCount_ggt(uint8_t aX, uint8_t aY, uint8_t aCount) {
    ENGINE_drawBitmapByIndex(aX, aY + 1, EII_PISTOL_CS);
    ENGINE_fillRectangle(aX + IMG_pistol_cs->width + 10, aY, 22, 14, 0); // clean space for count number
    ENGINE_drawInt(aX + IMG_pistol_cs->width + 10 + 11, aY, aCount, 'C', 1);
}

void DISPLAY_drawRank_gg(uint8_t aX, uint8_t aY, uint8_t aRank, uint8_t aKills) {
    ENGINE_fillRectangle(aX, aY, 59, 27, 0);
    if (aKills == 255) {
        ENGINE_drawBitmapByIndex(aX + 10, aY, EII_MEDAILE);
        ENGINE_drawInt(aX + IMG_medaile->width + 25, aY + 7, aRank, 'C', 1);
    } else {
        ENGINE_drawInt(aX + 13, aY + 7, aRank, 'C', 1);
        ENGINE_drawBitmapByIndex(aX + 32, aY + 8, EII_SKULL_CS);
        if (aKills > 9) {
            aKills = 9;
        }
        ENGINE_drawInt(aX + 51, aY + 7, aKills, 'C', 1);
    }
}

void DISPLAY_health(uint8_t aX, uint8_t aY, uint8_t aSize) {
    uint8_t lHealth = ENGINE_getHealth();
    uint8_t lNmbr = lHealth / 25;
    tImage *lHeartFull;
    tImage *lHeartEmpty;
    uint16_t lHeartFullIndex;
    uint16_t lHeartEmptyIndex;
    uint8_t lBitmapPart;
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t h;
    uint8_t tmp_byte = 0;
    uint8_t bytes_per_row;
    uint8_t lSpace = 0;
    if (aSize == 2) {
        lHeartFull = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART_SMALL);        // IMG_heart_small;
        lHeartEmpty = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART_SMALL_EMPTY); // IMG_heart_small_empty;
    } else if (aSize == 3) {
        lHeartFull = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART_SMALL2);        // IMG_heart_small2;
        lHeartEmpty = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART_SMALL2_EMPTY); // IMG_heart_small2_empty;
    } else {
        lHeartFull = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART);        // IMG_heart;
        lHeartEmpty = ENGINE_getBitmapDimension(NULL, NULL, EII_HEART_EMPTY); // IMG_heart_empty;
    }
    lSpace = lHeartEmpty->width + 1;
    lBitmapPart = (lHealth % 25) * lHeartFull->width / 25;
    bytes_per_row = lHeartFull->width / 8;
    if (lHeartFull->width % 8 != 0) {
        bytes_per_row++;
    }

    ENGINE_fillRectangle(aX, aY, lHeartFull->width + lSpace * 3, lHeartFull->height, 0);
    for (i = 0; i < lNmbr; i++) {
        ENGINE_drawBitmapByIndex(aX + lSpace * i, aY, lHeartFullIndex);
    }

    for (h = 0; h < lHeartFull->height; h++) {
        for (j = 0; j < (lBitmapPart); j += 8) {
            tmp_byte = lHeartFull->data[h * bytes_per_row + j / 8];
            for (k = 0; k < 8; k++) {
                if (j + k == (lBitmapPart)) {
                    k = 8;
                } else if ((tmp_byte & (1 << (7 - k))) != 0) {
                    ENGINE_drawPixel(aX + j + k + lSpace * i, aY + h, 1);
                }
            }
        }
    }

    for (; i < 4; i++) {
        ENGINE_drawBitmapByIndex(aX + lSpace * i, aY, lHeartEmptyIndex);
    }
}

void DISPLAY_bullets(uint8_t aX, uint8_t aY, uint8_t aBulletCount, uint8_t aMagazineCount) {
    // ENGINE_drawBitmapByIndex(aX, aY, EII_AMMO);
    // ENGINE_drawBitmapByIndex(aX + IMG_ammo->width + 1, aY, EII_AMMO);
    // ENGINE_drawBitmapByIndex(aX + 2 * IMG_ammo->width, aY + 1, EII_AMMO);
    ENGINE_fillRectangle(aX + 8, aY, 50, 22, 0); // clean space for bullets number
    // ENGINE_fillRectangle(aX + 50, aY, 11, 22, 0); // clean space for bullets number
    if (aBulletCount == 0xFF) {
        // ENGINE_drawChar(aX + 3 * IMG_ammo->width + 10 + 11 + 2 - 5, aY + 2, 236, 1);
        // ENGINE_fillRectangle(aX + 8, aY, 50, 22, 0); // clean space for bullets number
        ENGINE_drawBitmapByIndex(aX + 2 * IMG_ammo->width, aY + 1, EII_AMMO);
        ENGINE_drawChar(aX + 3 * IMG_ammo->width + 10 + 11 - 15, aY + 2, 'o', 1);
        ENGINE_drawChar(aX + 3 * IMG_ammo->width + 10 + 11 - 6, aY + 2, 'o', 1);
    } else {
        ENGINE_drawInt(aX + 3 * IMG_ammo->width + 10 - 2, aY + 4, aBulletCount, 'R', 1);
        // ENGINE_drawChar(aX + 3 * IMG_ammo->width + 10 , aY + 2, '|', 1);
        ENGINE_drawBitmapByIndex(aX + 3 * IMG_ammo->width + 10, aY + 1, EII_AMMO);
        ENGINE_drawInt(aX + 3 * IMG_ammo->width + 10 + 10 + 1, aY + 4, aMagazineCount, 'L', 1);
    }
}

void DISPLAY_bonus(uint8_t aBonusType) {
    switch (aBonusType) {
    case 1:
        ENGINE_drawBitmapByIndex(5, 13, EII_MACHINEGUN_BIG);
        ENGINE_drawString(37, 0, "MACHINEGUN", 0);
        break;
    case 2:
        ENGINE_drawBitmapByIndex(5, 15, EII_INVISIBILITY_BIG);
        ENGINE_drawString(27, 0, "INVISIBILITY", 0);
        break;
    case 3:
        ENGINE_drawBitmapByIndex(5, 10, EII_FLASH);
        ENGINE_drawString(32, 0, "IMMORTALITY", 0);
        break;
    default:
        break;
    }
}

void DISPLAY_bonusTime(uint16_t aTime) {
    uint8_t lX = 80;
    uint8_t lY = 25;
    ENGINE_fillRectangle(lX, lY, 47, 14, 0);
    ENGINE_drawInt(lX + 20, lY, aTime / 100, 'R', 1);
    ENGINE_drawChar(lX + 20, lY, '.', 1);
    ENGINE_drawInt(lX + 32, lY, (aTime / 10) % 10, 'L', 1);
}

void DISPLAY_killed(uint8_t aPlayerCode) {
    uint8_t lPlayerName[21] = {0};
    uint8_t lPlayerNameLength = 0;
    if (aPlayerCode <= 100) {
        lPlayerNameLength = ENGINE_getPlayerName(lPlayerName, aPlayerCode);
        ENGINE_drawBitmapByIndex(16, 15, EII_SKULL_SMALL);
    } else {
        lPlayerNameLength = "Mine";
        ENGINE_drawBitmapByIndex(16, 4, EII_BOMB);
    }

    if (lPlayerNameLength < 6) {
        ENGINE_drawString(88 - (lPlayerNameLength / 2) * 11, 25, lPlayerName, 1);
    } else {
        if (lPlayerNameLength > 10) {
            lPlayerNameLength = 12;
            lPlayerName[9] = '.';
            lPlayerName[10] = '.';
            lPlayerName[11] = '.';
            lPlayerName[12] = '\0';
        }
        ENGINE_drawString(88 - (lPlayerNameLength / 2) * 6, 30, lPlayerName, 0);
    }
}

void DISPLAY_hit(uint8_t aPlayerCode) {
    uint8_t lPlayerName[21] = {0};
    uint8_t lPlayerNameLength = 0;
    lPlayerNameLength = ENGINE_getPlayerName(lPlayerName, aPlayerCode);
    ENGINE_drawBitmapByIndex(4, 10, EII_AIM);
    if (lPlayerNameLength < 6) {
        ENGINE_drawString(88 - (lPlayerNameLength / 2) * 11, 25, lPlayerName, 1);
    } else {
        if (lPlayerNameLength > 10) {
            lPlayerNameLength = 12;
            lPlayerName[9] = '.';
            lPlayerName[10] = '.';
            lPlayerName[11] = '.';
            lPlayerName[12] = '\0';
        }
        ENGINE_drawString(88 - (lPlayerNameLength / 2) * 6, 30, lPlayerName, 0);
    }
}

void DISPLAY_killed_cs(uint8_t aPlayerCode, uint8_t aWeaponIndex) {
    uint8_t i = 0;
    uint8_t lPlayerName[21] = {0};
    uint8_t lPlayerNameLength = 0;
    uint8_t lTotalWidth = 0;
    uint8_t lX = 0;
    uint8_t lSize = 0;
    tImage *lWeapon;
    lWeapon = *gvpWeaponsAllList[aWeaponIndex];
    lPlayerNameLength = ENGINE_getPlayerName(lPlayerName, aPlayerCode);
    ENGINE_drawBitmapByIndex(41, 1, EII_SKULL_SMALL);

    lTotalWidth = lWeapon->width + 18 + 2; // pistol width, 3 arrows width, two onepixel spaces
    if (lPlayerNameLength * 11 <= DISPLAY_WIDTH - lTotalWidth) {
        lTotalWidth += lPlayerNameLength * 11; // add player name width
        lSize = 1;
    } else {
        if (lPlayerNameLength * 6 > DISPLAY_WIDTH - lTotalWidth) {
            lPlayerNameLength = (DISPLAY_WIDTH - lTotalWidth) / 6;
            for (i = 1; i < 4; i++) {
                if (lPlayerNameLength - i > 0) {
                    lPlayerName[lPlayerNameLength - i] = '.';
                }
            }
            lPlayerName[lPlayerNameLength] = '\0';
        }
        lTotalWidth += lPlayerNameLength * 6; // add player name width
        // ENGINE_drawString(92 - (lPlayerNameLength / 2) * 6, 50, lPlayerName, 0);
    }
    lX = 64 - lTotalWidth / 2;
    ENGINE_drawBitmapByIndex(lX, 41, lWeaponIndex);
    lX += lWeapon->width + 1;
    ENGINE_drawString(lX, 46, ">>>", 0);
    lX += 18 + 1;
    ENGINE_drawString(lX, 45 - lSize * 3, lPlayerName, lSize);
}

void DISPLAY_hit_cs(uint8_t aPlayerCode, uint8_t aWeaponIndex, uint8_t aWeaponObtainedIndex) {
    uint8_t i = 0;
    uint8_t lPlayerName[21] = {0};
    uint8_t lPlayerNameLength = 0;
    uint8_t lTotalWidth = 0;
    uint8_t lX = 0;
    uint8_t lSize = 0;
    tImage *lWeapon;
    lWeapon = *gvpWeaponsAllList[aWeaponIndex];
    lPlayerNameLength = ENGINE_getPlayerName(lPlayerName, aPlayerCode);
    if (aWeaponObtainedIndex == 255) {
        ENGINE_drawBitmapByIndex(41, 1, EII_AIM_SMALL);
    } else {
        uint8_t lX = 64 - (*gvpWeaponsAllList[aWeaponObtainedIndex])->width / 2;
        uint8_t lY = 19 - (*gvpWeaponsAllList[aWeaponObtainedIndex])->height / 2;
        ENGINE_drawBitmapByIndex(lX, lY, (*gvpWeaponsAllList[aWeaponObtainedIndex])->width, (*gvpWeaponsAllList[aWeaponObtainedIndex])->height, (*gvpWeaponsAllList[aWeaponObtainedIndex])->data);
    }

    lTotalWidth = lWeapon->width + 18 + 2; // pistol width, 3 arrows width, two onepixel spaces
    if (lPlayerNameLength * 11 <= DISPLAY_WIDTH - lTotalWidth) {
        lTotalWidth += lPlayerNameLength * 11; // add player name width
        lSize = 1;
    } else {
        if (lPlayerNameLength * 6 > DISPLAY_WIDTH - lTotalWidth) {
            lPlayerNameLength = (DISPLAY_WIDTH - lTotalWidth) / 6;
            for (i = 1; i < 4; i++) {
                if (lPlayerNameLength - i > 0) {
                    lPlayerName[lPlayerNameLength - i] = '.';
                }
            }
            lPlayerName[lPlayerNameLength] = '\0';
        }
        lTotalWidth += lPlayerNameLength * 6; // add player name width
        // ENGINE_drawString(92 - (lPlayerNameLength / 2) * 6, 50, lPlayerName, 0);
    }
    lX = 64 - lTotalWidth / 2;
    ENGINE_drawBitmapByIndex(lX, 41, lWeaponIndex);
    lX += lWeapon->width + 1;
    ENGINE_drawString(lX, 46, ">>>", 0);
    lX += 18 + 1;
    ENGINE_drawString(lX, 45 - lSize * 3, lPlayerName, lSize);

    /*
    ENGINE_drawBitmapByIndex(0, 46, EII_PISTOL_SMALL);
    ENGINE_drawString(55, 48, ">>>", 1);
    if (lPlayerNameLength < 6) {
        ENGINE_drawString(92 - (lPlayerNameLength / 2) * 11, 48, lPlayerName, 1);
    } else {
        if (lPlayerNameLength > 10) {
            lPlayerNameLength = 12;
            lPlayerName[9] = '.';
            lPlayerName[10] = '.';
            lPlayerName[11] = '.';
            lPlayerName[12] = '\0';
        }
        ENGINE_drawString(92 - (lPlayerNameLength / 2) * 6, 50, lPlayerName, 0);
    }*/
}

void DISPLAY_buying_cs(int8_t aItemIndex,
                       uint8_t aItemState,
                       uint8_t aDefuseEnabled,
                       uint8_t aSwipe,
                       uint16_t aMoney,
                       uint16_t aPrice,
                       uint8_t aAmmo,
                       uint8_t aMagazine,
                       uint8_t *apWeaponsList,
                       uint8_t aWeaponListIndex,
                       uint8_t aWeaponListLength,
                       uint8_t aBombHolding,
                       uint16_t aTimeBuying) {
    typedef enum {
        itemBlocked,
        itemAvailable,
        itemBought,
        itemAmmo
    } itemStateType;
    uint8_t i = 0;
    tImage *lpItem1;
    tImage *lpItem2;
    tImage *lpItem3;
    uint8_t *lpItemNameList[CS_WEAPONS_ALL_NMBR + CS_NONWEAPON_ITEMS_NMBR] = {0};
    tImage *lpItemList[CS_WEAPONS_ALL_NMBR + CS_NONWEAPON_ITEMS_NMBR] = {0};
    uint8_t lItemNameLength = 0;
    int16_t lX1, lX2, lX3;
    uint8_t lY1, lY2, lY3;
    int16_t lDist1, lDist2, lDist3;
    uint8_t lItemCount = aWeaponListLength + 2;
    uint8_t lWeaponsCount = aWeaponListLength;
    uint8_t lItemIsShield = 0;
    const uint8_t lcPixels = 10;
    const uint8_t lcMiddleX = 64;
    const uint8_t lcMiddleY = 28;
    const uint8_t lcKevlarIndex = lWeaponsCount + 1;
    const uint8_t lcShieldIndex = 11;

    if (aDefuseEnabled == 1) {
        lItemCount++;
    }

    if (aItemIndex == lcShieldIndex) {
        lItemIsShield = 1;
    }

    for (i = 0; i < lWeaponsCount; i++) {
        lpItemList[i] = *gpItemList[apWeaponsList[i]];
        lpItemNameList[i] = gpItemNameList[apWeaponsList[i]];
    }
    for (i = 0; i < CS_NONWEAPON_ITEMS_NMBR; i++) {
        lpItemList[lWeaponsCount + i] = *gpItemList[CS_WEAPONS_ALL_NMBR + i];
        lpItemNameList[lWeaponsCount + i] = gpItemNameList[CS_WEAPONS_ALL_NMBR + i];
    }

    if (aItemIndex < CS_WEAPONS_ALL_NMBR) {
        aItemIndex = aWeaponListIndex;
    } else {
        aItemIndex = aItemIndex - CS_WEAPONS_ALL_NMBR + lWeaponsCount;
    }

    lpItem1 = lpItemList[(aItemIndex - 1 + lItemCount) % lItemCount];
    lpItem2 = lpItemList[aItemIndex];
    lpItem3 = lpItemList[(aItemIndex + 1) % lItemCount];

    lX1 = lcPixels - lpItem1->width;
    lX2 = lcMiddleX - lpItem2->width / 2;
    lX3 = DISPLAY_WIDTH - lcPixels;
    lY1 = lcMiddleY - lpItem1->height / 2;
    lY2 = lcMiddleY - lpItem2->height / 2;
    lY3 = lcMiddleY - lpItem3->height / 2;

    while (lpItemNameList[aItemIndex][lItemNameLength] != 0 && lItemNameLength < 6) {
        lItemNameLength++;
    }

    ENGINE_drawLine(128 - aTimeBuying * 128 / 1000, 41, 128, 41, 1);
    ENGINE_drawLine(0, 15, aTimeBuying * 128 / 1000, 15, 1);

    ENGINE_drawChar(0, 46, 36, 1);
    ENGINE_drawInt(15, 46, aMoney, 'L', 1);

    if (aBombHolding == 1) {
        ENGINE_drawBitmapByIndex(110, 0, EII_BOMB_MINIATURE);
    }

    if (aSwipe == 0) {
        uint8_t lXName = 0;
        uint8_t lXNameLength = lItemNameLength * 6 + 10 - lItemIsShield * 5; // 6 is char size on display and 10 is space between anme and price
        // ENGINE_drawString(0, 48, "Price", 0);
        if (aItemState != itemBought) {
            uint8_t lXDollar = 61;
            uint8_t lXPrice = 68;
            uint16_t lPriceTemp = aPrice;
            while (lPriceTemp > 0) {
                lPriceTemp /= 10;
                lXDollar -= 3;
            }
            lXPrice += lXNameLength / 2;
            lXDollar += lXNameLength / 2;
            lXName = lXDollar - lXNameLength;
            ENGINE_drawInt(lXPrice, 5, aPrice, 'C', 0);
            ENGINE_drawChar(lXDollar, 5, 36, 0);
        } else {
            lXName = 68 - lXNameLength / 2;
        }
        ENGINE_drawString(lXName, 5, lpItemNameList[aItemIndex], 0);

        if (lItemIsShield == 0) {
            if ((aItemState == itemBought || aItemState == itemAmmo) || (aItemState == itemAvailable && aItemIndex == lcKevlarIndex && aAmmo > 0)) {
                if (aItemIndex < lWeaponsCount) {
                    ENGINE_drawInt(103 - 2, 46, aAmmo, 'R', 1);
                    ENGINE_drawBitmapByIndex(103, 43, EII_AMMO);
                    ENGINE_drawInt(103 + 10 + 1, 46, aMagazine, 'L', 1);
                } else if (aItemIndex == lcKevlarIndex) {
                    ENGINE_drawInt(115, 46, aAmmo, 'R', 1);
                    ENGINE_drawChar(115, 46, '%', 1);
                }
            } else {
                if (aItemIndex < lWeaponsCount) {
                    ENGINE_drawChar(88, 46, '-', 1);
                    ENGINE_drawBitmapByIndex(103, 43, EII_AMMO);
                    ENGINE_drawChar(103 + 10 + 1, 46, '-', 1);
                } else if (aItemIndex == lcKevlarIndex) {
                    ENGINE_drawChar(105, 46, '-', 1);
                }
            }
        }

        switch (aItemState) {
        case itemBlocked:
            ENGINE_drawBitmapByIndex(5, 0, EII_BASKET);
            ENGINE_drawLine(4, 11, 30, 2, 1);
            ENGINE_drawLine(4, 12, 30, 3, 1);

            break;
        case itemAvailable:
            ENGINE_drawBitmapByIndex(5, 0, EII_BASKET);
            break;
        case itemBought:
            break;
        case itemAmmo:
            ENGINE_drawBitmapByIndex(3, 0, EII_BULLETS);
            break;
        default:
            break;
        }

        ENGINE_drawBitmapByIndex(lX1, lY1, lpItem1Index);
        ENGINE_drawBitmapByIndex(lX2, lY2, lpItem2Index);
        ENGINE_drawBitmapByIndex(lX3, lY3, lpItem3Index);
    } else {

        if (aSwipe < lcPixels) {
            lDist1 = aSwipe;
        } else if (aSwipe < (100 - lcPixels)) {
            lDist1 = 0;
            lX1 = DISPLAY_WIDTH;
        } else {
            lDist1 = aSwipe - 100 + lcPixels;
            lpItem1 = lpItemList[(aItemIndex + 2) % lItemCount];
            lX1 = DISPLAY_WIDTH;
        }

        lDist2 = (lX2 + lpItem2->width - lcPixels) * aSwipe / 100;
        lDist3 = (lX3 + lpItem3->width / 2 - lcMiddleX) * aSwipe / 100;

        /*lDist1 = aSwipe;
        lDist2 = aSwipe;
        lDist3 = aSwipe;*/

        ENGINE_drawBitmapByIndex(lX1 - lDist1, lY1, lpItem1Index);
        ENGINE_drawBitmapByIndex(lX2 - lDist2, lY2, lpItem2Index);
        ENGINE_drawBitmapByIndex(lX3 - lDist3, lY3, lpItem3Index);
    }
}

void DISPLAY_drawBomb(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_BOMB_SMALL);
}

void DISPLAY_drawBombSmall(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_BOMB_MINIATURE);
}

void DISPLAY_drawDefuse(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_DEFUSE);
}

void DISPLAY_drawDefuseSmall(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_DEFUSESMALL);
}

void DISPLAY_drawStickman(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_STICKMAN);
}

void DISPLAY_drawAgent(uint8_t aX, uint8_t aY) {
    ENGINE_drawBitmapByIndex(aX, aY, EII_AGENT);
}

void DISPLAY_drawPlayers(uint8_t aX, uint8_t aY, uint8_t aTeam, uint8_t aPlayersCountCT, uint8_t aPlayersCountTerr) {
    uint8_t lCount1, lCount2;
    if (aTeam == teamCT) {
        lCount1 = aPlayersCountCT;
        lCount2 = aPlayersCountTerr;
    } else {
        lCount1 = aPlayersCountTerr;
        lCount2 = aPlayersCountCT;
    }
    if (lCount1 > 9) {
        lCount1 = 9;
    }
    if (lCount2 == 250) {
        ENGINE_drawInt(aX + 7, aY, lCount1, 'L', 1);
        ENGINE_drawBitmapByIndex(aX + 20, aY, EII_STICKMAN);
    } else {
        if (lCount2 > 9) {
            lCount2 = 9;
        }
        ENGINE_drawInt(aX + 2, aY, lCount1, 'L', 1);
        ENGINE_drawInt(aX + 25, aY, lCount2, 'L', 1);
        ENGINE_drawBitmapByIndex(aX + 15, aY, EII_STICKMAN);
    }
}

/* aOptions - for additional info to show with weapon
 *   - silencer
 *   - burst mode
 *   - shield with weapon
 */
void DISPLAY_drawWeapon(uint8_t aX, uint8_t aY, uint8_t aWeapon, uint8_t aOptions) {
    typedef enum {
        weaponKnife,
        weaponUSP,
        weaponGlock,
        weaponDeagle,
        weaponMP5,
        weaponP90,
        weaponM4,
        weaponAK47,
        weaponAUG,
        weaponSG552,
        weaponAWP,
        weaponShield,
        weaponNone = 255
    } weaponListType;

    ENGINE_fillRectangle(aX, aY, 59, 27, 0);
    // ENGINE_fillRectangle(aX + 49, aY, 10, 17, 0);
    switch (aWeapon) {
    case weaponKnife:
        ENGINE_drawBitmapByIndex(aX + 8, aY + 8, EII_KNIFE);
        break;
    case weaponUSP:
        ENGINE_drawBitmapByIndex(aX + 13, aY + 3, EII_USP);
        break;
    case weaponGlock:
        ENGINE_drawBitmapByIndex(aX + 12, aY + 3, EII_PISTOL_SMALL);
        aOptions = aOptions * 2;
        break;
    case weaponDeagle:
        ENGINE_drawBitmapByIndex(aX + 15, aY + 3, EII_DEAGLE);
        break;
    case weaponMP5:
        ENGINE_drawBitmapByIndex(aX + 5, aY + 3, EII_MP5);
        break;
    case weaponP90:
        ENGINE_drawBitmapByIndex(aX + 3, aY + 1, EII_P90);
        break;
    case weaponM4:
        ENGINE_drawBitmapByIndex(aX, aY + 5, EII_M4);
        break;
    case weaponAK47:
        ENGINE_drawBitmapByIndex(aX, aY + 4, EII_AK47_SMALL_2);
        break;
    case weaponAUG:
        ENGINE_drawBitmapByIndex(aX, aY + 3, EII_AUG);
        break;
    case weaponSG552:
        ENGINE_drawBitmapByIndex(aX, aY + 1, EII_SG552);
        break;
    case weaponAWP:
        ENGINE_drawBitmapByIndex(aX, aY + 5, EII_AWP);
        break;
    case weaponShield:
        if (aOptions == 0) {
            ENGINE_drawBitmapByIndex(aX + 22, aY + 2, EII_TACTICAL_SHIELD);
        } else {
            ENGINE_drawBitmapByIndex(aX + 5, aY + 2, EII_TACTICAL_SHIELD);
            switch (aOptions & 0x0F) {
            case weaponUSP:
                ENGINE_drawBitmapByIndex(aX + 27, aY + 3, EII_USP);
                break;
            case weaponGlock:
                ENGINE_drawBitmapByIndex(aX + 26, aY + 3, EII_PISTOL_SMALL);
                break;
            case weaponDeagle:
                ENGINE_drawBitmapByIndex(aX + 23, aY + 3, EII_DEAGLE);
                break;
            default:
                break;
            }
        }
        break;
    }

    if (aOptions == 1) {
        ENGINE_drawBitmapByIndex(aX + 41, aY + 20, EII_SILENCER);
    } else if (aOptions == 2) {
        ENGINE_drawBitmapByIndex(aX + 43, aY + 16, EII_BURST_MODE2);
    }
}

void DISPLAY_drawWeaponReceived(uint8_t aWeapon, uint8_t aAmmo, uint8_t aMagazine) {

    uint8_t lItemNameLength = 0;
    uint8_t lXName = 0;
    uint8_t lXNameLength = 0;
    int16_t lX;
    uint8_t lY;
    int16_t lDist1, lDist2, lDist3;
    uint8_t lItemIsShield = 0;
    const uint8_t lcPixels = 10;
    const uint8_t lcMiddleX = 64;
    const uint8_t lcMiddleY = 28;
    const uint8_t lcShieldIndex = 11;

    lX = lcMiddleX - (*gpItemList[aWeapon])->width / 2;
    lY = lcMiddleY - (*gpItemList[aWeapon])->height / 2;

    while (gpItemNameList[aWeapon][lItemNameLength] != 0 && lItemNameLength < 6) {
        lItemNameLength++;
    }

    if (aWeapon == lcShieldIndex) {
        lItemIsShield = 1;
    }

    lXNameLength = lItemNameLength * 6 + 10; // 6 is char size on display and 10 is space between anme and price
    lXName = 68 - lXNameLength / 2;
    ENGINE_drawString(lXName, 5, gpItemNameList[aWeapon], 0);

    if (lItemIsShield == 0) {
        ENGINE_drawInt(103 - 2, 46, aAmmo, 'R', 1);
        ENGINE_drawBitmapByIndex(103, 43, EII_AMMO);
        ENGINE_drawInt(103 + 10 + 1, 46, aMagazine, 'L', 1);
    }

    ENGINE_drawBitmapByIndex(lX, lY, (*gpItemList[aWeapon])->width, (*gpItemList[aWeapon])->height, (*gpItemList[aWeapon])->data);
}

void DISPLAY_drawBarSegmented(uint8_t aX, uint8_t aY, uint8_t aPercentage) {
    uint8_t i;

    ENGINE_drawBar(aX, aY, 78, 10, aPercentage, 'H');

    for (i = 0; i < 13; i++) {
        uint8_t lX = i * 6 + aX;
        ENGINE_drawLine(lX, aY + 1, lX, aY + 9, 1);
        ENGINE_drawLine(lX + 4, aY + 1, lX + 4, aY + 9, 1);
        ENGINE_drawLine(lX + 5, aY, lX + 5, aY + 10, 0);
        ENGINE_drawPixel(lX, aY, 0);
        ENGINE_drawPixel(lX, aY + 9, 0);
        ENGINE_drawPixel(lX + 4, aY, 0);
        ENGINE_drawPixel(lX + 4, aY + 9, 0);
    }
}

void DISPLAY_drawBarSegmentedExpert(uint8_t aX, uint8_t aY, uint8_t aPercentage, uint8_t aWidth, uint8_t aHeight, uint8_t aSegmentCount) {
    uint8_t i;

    uint8_t lSegmentWidth = aWidth / aSegmentCount;
    uint8_t lXo;
    uint8_t lYo;

    aWidth = lSegmentWidth * aSegmentCount;

    ENGINE_drawBar(aX, aY, aWidth, aHeight, aPercentage, 'H');

    if (lSegmentWidth > 3 && aHeight > 2) {
        lXo = lSegmentWidth - 2;
        lYo = aHeight - 1;

        for (i = 0; i < aSegmentCount; i++) {
            uint8_t lX = i * lSegmentWidth + aX;
            ENGINE_drawLine(lX, aY + 1, lX, aY + lYo, 1);
            ENGINE_drawLine(lX + lXo, aY + 1, lX + lXo, aY + lYo, 1);
            ENGINE_drawLine(lX + lXo + 1, aY, lX + lXo + 1, aY + aHeight, 0);
            ENGINE_drawPixel(lX, aY, 0);
            ENGINE_drawPixel(lX, aY + lYo, 0);
            ENGINE_drawPixel(lX + lXo, aY, 0);
            ENGINE_drawPixel(lX + lXo, aY + lYo, 0);
        }
    }
}

void DISPLAY_info_cs(uint8_t aTeam,
                     uint8_t aWhoWins,
                     uint8_t aWinsCT,
                     uint8_t aWinsTerr,
                     uint16_t aKills,
                     uint16_t aDeaths,
                     uint16_t aMoney,
                     uint8_t aAnimation,
                     uint8_t aPlayersCountCT,
                     uint8_t aPlayersCountTerr,
                     uint16_t aDamageTotal,
                     uint16_t aDamageInRound) {
    if (aWhoWins < 250) {
        /*show who wins on whole screen*/
        ENGINE_drawBitmapByIndex(5, 2, EII_TROPHY);
        if (aWhoWins == 0) {
            ENGINE_drawString(80, 15, "CT", 1);
        } else {
            ENGINE_drawString(85, 15, "T", 1);
        }
        ENGINE_drawString(75, 35, "WIN", 1);

    } else {
        /*show basic info after round*/
        DISPLAY_initLayout(5);
        DISPLAY_rank(64, 32, 5);

        /*rounds score*/
        ENGINE_drawString(15, 6, "CT", 0);
        ENGINE_drawString(37, 6, "T", 0);
        ENGINE_drawInt(21, 18, aWinsCT, 'C', 0);
        ENGINE_drawInt(40, 18, aWinsTerr, 'C', 0);

        /*kills and deaths && damage*/
        if ((aAnimation & 0xF0) == 0) {
            ENGINE_drawBitmapByIndex(78, 4, EII_PISTOL_CS);
            ENGINE_drawBitmapByIndex(107, 4, EII_SKULL_CS);
            ENGINE_drawInt(87, 18, aKills, 'C', 0);
            ENGINE_drawInt(112, 18, aDeaths, 'C', 0);
        } else {
            uint8_t lX = 115;
            if (aDamageTotal >= 1000) {
                lX += 10;
            } else if (aDamageTotal >= 100) {
                lX += 5;
            }
            ENGINE_drawBitmapByIndex(86, 6, EII_LIGHTNING_CS);
            ENGINE_drawBitmapByIndex(85, 17, EII_SUM);
            ENGINE_drawInt(lX, 7, aDamageInRound, 'R', 0);
            ENGINE_drawInt(lX, 18, aDamageTotal, 'R', 0);
        }

        /*money*/
        ENGINE_drawInt(32, 45, aMoney, 'C', 0);
        uint8_t lXDollar = 25;
        if (aMoney == 0) {
            lXDollar -= 3;
        }
        while (aMoney > 0) {
            aMoney /= 10;
            lXDollar -= 3;
        }
        ENGINE_drawChar(lXDollar, 45, 36, 0);

        /*go to spawn || players count*/
        if (aPlayersCountCT != 255 && (aPlayersCountCT != 0 || aPlayersCountTerr != 0)) {
            DISPLAY_drawPlayers(80, 42, aTeam, aPlayersCountCT, aPlayersCountTerr);
        } else {
            ENGINE_drawBitmapByIndex(100, 36, EII_BASE);
            switch (aAnimation & 0x0F) {
            case 0:
                break;
            case 3:
                ENGINE_drawBitmapByIndex(92, 40, EII_ARROW2);
            case 2:
                ENGINE_drawBitmapByIndex(85, 40, EII_ARROW2);
            case 1:
                ENGINE_drawBitmapByIndex(78, 40, EII_ARROW2);
                break;
            default:
                break;
            }
        }
    }
}

void DISPLAY_info_gg(uint16_t aKills, uint16_t aDeaths) {
    /*kills and deaths*/
    ENGINE_fillRectangle(3, 35, 59, 27, 0);
    ENGINE_drawBitmapByIndex(14, 36, EII_PISTOL_CS);
    ENGINE_drawBitmapByIndex(43, 36, EII_SKULL_CS);
    ENGINE_drawInt(23, 50, aKills, 'C', 0);
    ENGINE_drawInt(48, 50, aDeaths, 'C', 0);
}

void DISPLAY_spawn_animation(uint8_t aAnimation) {

    ENGINE_fillRectangle(67, 35, 59, 27, 0);

    ENGINE_drawBitmapByIndex(100, 36, EII_BASE);
    switch (aAnimation) {
    case 0:
        break;
    case 3:
        ENGINE_drawBitmapByIndex(92, 40, EII_ARROW2);
    case 2:
        ENGINE_drawBitmapByIndex(85, 40, EII_ARROW2);
    case 1:
        ENGINE_drawBitmapByIndex(78, 40, EII_ARROW2);
        break;
    default:
        break;
    }
}

void DISPLAY_agent(uint8_t aAgentCount) {
    if (aAgentCount == 0) {
        ENGINE_drawBitmapByIndex(44, 2, EII_AGENT);
        ENGINE_drawString(31, 46, "Agent!", 1);
    } else if (aAgentCount == 1) {
        ENGINE_drawBitmapByIndex(20, 2, EII_AGENT);
        ENGINE_drawBitmapByIndex(68, 2, EII_AGENT);
        ENGINE_drawString(9, 46, "2x IMG_Agent!!", 1);
    } else {
        ENGINE_drawBitmapByIndex(0, 2, EII_AGENT);
        ENGINE_drawBitmapByIndex(44, 2, EII_AGENT);
        ENGINE_drawBitmapByIndex(88, 2, EII_AGENT);
        ENGINE_drawString(3, 46, "3x IMG_Agent!!!", 1);
    }
}

void DISPLAY_orbReceived(uint8_t aOrbType) {
    if (aOrbType < 4) {
        uint8_t lX = 30 - (*gpOrbImage[aOrbType])->width / 2;
        uint8_t lY = 32 - (*gpOrbImage[aOrbType])->height / 2;
        ENGINE_drawBitmapByIndex(lX, lY, (*gpOrbImage[aOrbType])->width, (*gpOrbImage[aOrbType])->height, (*gpOrbImage[aOrbType])->data);

        lX = 94 - (strlen(gpOrbName[aOrbType]) * 3); // * 6 / 2
        ENGINE_drawString(lX, 28, gpOrbName[aOrbType], 0);
    }
}

void DISPLAY_drawOrbs(uint8_t aX, uint8_t aY, uint8_t aOrbs) {
    ENGINE_fillRectangle(aX, aY, 120, 27, 0);

    if (((aOrbs >> 0) & 0x01) != 0) {
        ENGINE_drawBitmapByIndex(aX + 16 - ENGINE_getBitmapDimension(NULL, NULL, EII_MACHINEGUN_SMALL)->width / 2, aY + 1, EII_MACHINEGUN_SMALL);
    } else {
        ENGINE_drawBitmapByIndex(aX + 16 - ENGINE_getBitmapDimension(NULL, NULL, EII_MACHINEGUN_SMALL_EMPTY)->width / 2, aY + 1, EII_MACHINEGUN_SMALL_EMPTY);
    }
    if (((aOrbs >> 1) & 0x01) != 0) {
        ENGINE_drawBitmapByIndex(aX + 46 - ENGINE_getBitmapDimension(NULL, NULL, EII_SHIELD)->width / 2, aY + 1, EII_SHIELD);
    } else {
        ENGINE_drawBitmapByIndex(aX + 46 - IMG_shield_empty->width / 2, aY + 1, EII_SHIELD_EMPTY);
    }
    if (((aOrbs >> 2) & 0x01) != 0) {
        ENGINE_drawBitmapByIndex(aX + 76 - IMG_flash_small->width / 2, aY + 1, EII_FLASH_SMALL);
    } else {
        ENGINE_drawBitmapByIndex(aX + 76 - IMG_flash_small_empty->width / 2, aY + 1, EII_FLASH_SMALL_EMPTY);
    }
    if (((aOrbs >> 3) & 0x01) != 0) {
        ENGINE_drawBitmapByIndex(aX + 106 - IMG_healing->width / 2, aY + 1, EII_HEALING);
    } else {
        ENGINE_drawBitmapByIndex(aX + 106 - IMG_healing_empty->width / 2, aY + 1, EII_HEALING_EMPTY);
    }
}

void DISPLAY_bans(void) {
    const uint8_t lXCentres[4] = {19, 49, 79, 109};
    const uint8_t lXPixels[21] = {34, 36, 38, 37, 35, 32, 31, 31, 32, 35, 37,
                                  43, 45, 46, 48, 49, 49, 48, 46, 45, 43};
    const uint8_t lYPixels[21] = {8, 6, 5, 5, 6, 9, 11, 17, 19, 22, 23, 5, 6,
                                  8, 9, 11, 17, 19, 20, 22, 23};
    uint8_t i = 0;

    /*icon*/
    ENGINE_drawCircle(40, 14, 10, 1);
    ENGINE_drawCircle(40, 14, 9, 1);
    ENGINE_drawLine(33, 20, 46, 7, 1);
    ENGINE_drawLine(34, 20, 46, 8, 1);
    ENGINE_drawLine(34, 21, 47, 8, 1);
    for (i = 0; i < 21; i++) {
        ENGINE_drawPixel(lXPixels[i], lYPixels[i], 1);
    }

    /*label*/
    ENGINE_drawString(60, 7, "BANS", 1);

    /*line*/
    ENGINE_drawLine(2, 28, 126, 28, 1);

    /*stickman icons*/
    ENGINE_drawBitmapByIndex(lXCentres[0] - IMG_stickman_run2->width / 2,
                             49 - IMG_stickman_run2->height, EII_STICKMAN_RUN2);
    ENGINE_drawBitmapByIndex(lXCentres[1] - IMG_stickman_climb->width / 2,
                             49 - IMG_stickman_climb->height, EII_STICKMAN_CLIMB);
    ENGINE_drawBitmapByIndex(lXCentres[2] - IMG_stickman_lying->width / 2,
                             49 - IMG_stickman_lying->height, EII_STICKMAN_LYING);
    ENGINE_drawBitmapByIndex(lXCentres[3] - IMG_stickman_fight2->width / 2,
                             49 - IMG_stickman_fight2->height, EII_STICKMAN_FIGHT2);

    /*stickman labels*/
    ENGINE_drawString(lXCentres[0] - 3 * 3, 51, "Run", 0);
    ENGINE_drawString(lXCentres[1] - 5 * 3, 51, "Climb", 0);
    ENGINE_drawString(lXCentres[2] - 3 * 3, 51, "Lie", 0);
    ENGINE_drawString(lXCentres[3] - 5 * 3, 51, "Fight", 0);
}

void DISPLAY_animationTwoHandsShooting(uint8_t aX, uint8_t aY, uint8_t aFrame) {
    uint8_t lYHand = 0;
    uint8_t lXHand = 0;
    if (aFrame > 31) {
        return;
    } else if (aFrame < 20) {
        lYHand = 19 - aFrame;
    } else if (aFrame > 21) {
        if (aFrame > 26) {
            aFrame = 52 - aFrame;
        }
        lXHand = aFrame - 21;
    }

    ENGINE_fillRectangle(aX, aY, 120, 48, 0);

#ifdef SIMULATION_PLUGIN
    ENGINE_drawBitmapByIndex(aX, aY, weapon_whiteIndex);
#else
    ENGINE_drawBitmapByIndex(aX, aY, EII_WEAPON_BLACK);
#endif

    ENGINE_clearBItmapByIndex(aX + 20, aY + 22 + lYHand, EII_HAND_BLACK);
    ENGINE_drawBitmapByIndex(aX + 20, aY + 22 + lYHand, EII_HAND);

    if (aFrame >= 20) {
        ENGINE_clearBItmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER_BLACK);
        ENGINE_drawBitmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER);
    }

    ENGINE_clearBItmapByIndex(aX + 53, aY + 14, EII_TRIGGER);
    ENGINE_drawBitmapByIndex(aX + 53 + lXHand, aY + 14, EII_TRIGGER);

    ENGINE_clearBItmapByIndex(aX + 50, aY + 12, EII_HAND_2_BLACK);
    ENGINE_drawBitmapByIndex(aX + 50, aY + 12, EII_HAND_2);

    if (aFrame > 21) {
        ENGINE_clearBItmapByIndex(aX + 50, aY + 15, EII_HAND_2_FINGER);
        ENGINE_drawBitmapByIndex(aX + 50 + lXHand, aY + 15, EII_HAND_2_FINGER);
    }
    if (aFrame > 20) {
        uint8_t lXCheck = aX + 10;
        uint8_t lYCheck = aY + 32;

        ENGINE_drawPixels(lXCheck, lYCheck + 1, 1, 4);
        ENGINE_drawPixels(lXCheck, lYCheck + 2, 1, 4);
        ENGINE_drawPixels(lXCheck + 1, lYCheck + 3, 1, 4);
        ENGINE_drawPixels(lXCheck + 1, lYCheck + 4, 1, 4);
        ENGINE_drawPixels(lXCheck + 2, lYCheck + 4, 1, 4);
        ENGINE_drawPixels(lXCheck + 3, lYCheck + 3, 1, 4);
        ENGINE_drawPixels(lXCheck + 4, lYCheck + 2, 1, 4);
        ENGINE_drawPixels(lXCheck + 5, lYCheck + 1, 1, 4);
        ENGINE_drawPixels(lXCheck + 6, lYCheck, 1, 4);
    }

    ENGINE_drawLine(20, 62, 50, 62, 1);
    ENGINE_drawLine(20, 63, 50, 63, 1);
}

void DISPLAY_animationReload(uint8_t aX, uint8_t aY, uint8_t aFrame) {
    uint8_t lYHand = 20;
    uint8_t lXHand = 0;

    if (aFrame > 32) {
        return;
    } else if (aFrame <= 1) {
        lYHand = 0;
    } else if (aFrame < 21) {
        lYHand = aFrame - 1;
    } else if (aFrame > 22) {
        if (aFrame > 27) {
            aFrame = 54 - aFrame;
        }
        lXHand = aFrame - 22;
    }

    ENGINE_fillRectangle(aX, aY, 120, 48, 0);

#ifdef SIMULATION_PLUGIN
    ENGINE_drawBitmapByIndex(aX, aY, weapon_whiteIndex);
#else
    ENGINE_drawBitmapByIndex(aX, aY, EII_WEAPON_BLACK);
#endif

    ENGINE_clearBItmapByIndex(aX + 20, aY + 22 + lYHand, EII_HAND_BLACK);
    ENGINE_drawBitmapByIndex(aX + 20, aY + 22 + lYHand, EII_HAND);

    if (aFrame <= 1) {
        ENGINE_clearBItmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER_BLACK);
        ENGINE_drawBitmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER);
    }

    ENGINE_clearBItmapByIndex(aX + 53, aY + 14, EII_TRIGGER);
    ENGINE_drawBitmapByIndex(aX + 53 + lXHand, aY + 14, EII_TRIGGER);

    ENGINE_clearBItmapByIndex(aX + 50, aY + 12, EII_HAND_2_BLACK);
    ENGINE_drawBitmapByIndex(aX + 50, aY + 12, EII_HAND_2);

    if (aFrame > 22) {
        ENGINE_clearBItmapByIndex(aX + 50, aY + 15, EII_HAND_2_FINGER);
        ENGINE_drawBitmapByIndex(aX + 50 + lXHand, aY + 15, EII_HAND_2_FINGER);
    }

    if (aFrame > 21) {
        uint8_t lXCheck = aX + 10;
        uint8_t lYCheck = aY + 32;

        ENGINE_drawPixels(lXCheck, lYCheck + 1, 1, 4);
        ENGINE_drawPixels(lXCheck, lYCheck + 2, 1, 4);
        ENGINE_drawPixels(lXCheck + 1, lYCheck + 3, 1, 4);
        ENGINE_drawPixels(lXCheck + 1, lYCheck + 4, 1, 4);
        ENGINE_drawPixels(lXCheck + 2, lYCheck + 4, 1, 4);
        ENGINE_drawPixels(lXCheck + 3, lYCheck + 3, 1, 4);
        ENGINE_drawPixels(lXCheck + 4, lYCheck + 2, 1, 4);
        ENGINE_drawPixels(lXCheck + 5, lYCheck + 1, 1, 4);
        ENGINE_drawPixels(lXCheck + 6, lYCheck, 1, 4);
    }

    ENGINE_drawLine(20, 62, 50, 62, 1);
    ENGINE_drawLine(20, 63, 50, 63, 1);
}

void DISPLAY_animationUserButton(uint8_t aX, uint8_t aY, uint8_t aFrame) {
    uint8_t lYHand = 0;
    uint8_t lXHand = 0;
    if (aFrame <= 5) {
        lYHand = aFrame;
        lXHand = lYHand / 3;
    } else if (aFrame > 5 && aFrame <= 10) {
        lYHand = 10 - aFrame;
        lXHand = lYHand / 3;
    } else {
        return;
    }

    ENGINE_fillRectangle(aX, aY, 120, 48, 0);
#ifdef SIMULATION_PLUGIN
    ENGINE_drawBitmapByIndex(aX, aY, weapon_whiteIndex);
#else
    ENGINE_drawBitmapByIndex(aX, aY, EII_WEAPON_BLACK);
#endif

    if (aFrame > 2 && aFrame < 8) {
        ENGINE_drawLine(aX + 19, aY + 19, aX + 29, aY + 19, 0);
        ENGINE_drawLine(aX + 19, aY + 19 - lYHand + 2, aX + 29,
                        aY + 19 - lYHand + 2, 1);
    }

    ENGINE_clearBItmapByIndex(aX + 20 - lXHand, aY + 22 - lYHand, EII_HAND_BLACK);
    ENGINE_drawBitmapByIndex(aX + 20 - lXHand, aY + 22 - lYHand, EII_HAND);

    ENGINE_clearBItmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER_BLACK);
    ENGINE_drawBitmapByIndex(aX + 25, aY + 16, EII_HAND_FINGER);

    ENGINE_clearBItmapByIndex(aX + 50, aY + 12, EII_HAND_2_BLACK);
    ENGINE_drawBitmapByIndex(aX + 50, aY + 12, EII_HAND_2);
}

/*void DISPLAY_drawCirclePart(uint8_t aX, uint8_t aY, uint8_t aPercentage) {
    uint8_t lQuadrant = 0;
    uint8_t lStartIndex = 92 - (aPercentage * 87 / 100);
    uint8_t i = 0;
    for (i = 0; i < 5; i++) {
        //setpixels(display_buffer_1, aX + circle_16_2[91][0], aY + circle_16_2[91][1] - i, 1, 3);
        ENGINE_drawPixel(aX + circle_16_2[91][0], aY + circle_16_2[91][1] - i, 1);
    }
    for (i = lStartIndex; i < 92; i++) {
        if (circle_16_2[i][0] >= 0 && circle_16_2[i][1] >= 0) {
            lQuadrant = 1;
        } else if (circle_16_2[i][0] < 0 && circle_16_2[i][1] >= 0) {
            lQuadrant = 2;
        } else if (circle_16_2[i][0] < 0 && circle_16_2[i][1] < 0) {
            lQuadrant = 3;
        } else if (circle_16_2[i][0] >= 0 && circle_16_2[i][1] < 0) {
            lQuadrant = 4;
        }
        //setpixels(display_buffer_1, aX + circle_16_2[i][0],aY + circle_16_2[i][1], 1, lQuadrant);
        ENGINE_drawPixel(aX + circle_16_2[i][0],
                         aY + circle_16_2[i][1], 1);
    }
}*/

void DISPLAY_drawBullet(uint8_t aX, uint8_t aY, uint8_t aType) {
    if (aType == 0) {
        ENGINE_drawBitmapByIndex(aX, aY, EII_AMMO_SMALL);
    } else if (aType == 1) {
        ENGINE_drawBitmapByIndex(aX, aY, EII_AMMO_SMALL_EMPTY);
    } else if (aType == 2) {
        ENGINE_drawBitmapByIndex(aX, aY, EII_AMMO_SMALL_INVERT);
    }
}

void DISPLAY_tutorialCountdown(uint8_t *apLabel, uint8_t aValue, uint8_t aPercentage) {
    uint8_t lLabelLength = strlen(apLabel);

    ENGINE_fillRectangle(20, 22, 88, 38, 0);

    ENGINE_drawString(63 - lLabelLength * 11 / 2, 6, apLabel, 1);

    ENGINE_drawInt(63, 33, aValue, 'C', 1);
    ENGINE_invertCircle(63, 40, 12);
    ENGINE_drawCirclePart(63, 40, 1, 100 - aPercentage, 1);
    // DISPLAY_drawCirclePart(63, 40, 100 - aPercentage);
}

void DISPLAY_tutorialShoot(uint8_t aCount) {
    uint8_t i = 0;
    const uint8_t lMaxCount = 5;
    char *lpReloadTitle = "SHOOT 5x!";

    if (aCount > lMaxCount) {
        aCount = lMaxCount;
    }

    lpReloadTitle[6] = (lMaxCount - aCount) + '0';
    ENGINE_drawString(63 - 9 * 11 / 2, 10, lpReloadTitle, 1);
    ENGINE_drawBitmapByIndex(10, 33, EII_DEAGLE);
    for (i = 0; i < aCount; i++) {
        ENGINE_drawBitmapByIndex(53 + i * 13, 28, EII_AMMO_BIG);
    }
    for (; i < lMaxCount; i++) {
        ENGINE_drawBitmapByIndex(53 + i * 13, 28, EII_AMMO_BIG_EMPTY);
    }
}

void DISPLAY_tutorialReload(uint8_t aCount, uint8_t aShootNow, uint8_t aType) {
    uint8_t i = 0;
    const uint8_t lMaxCount = 3;
    char *lpReloadTitle = "RELOAD 3x!";

    if (aCount > lMaxCount) {
        aCount = lMaxCount;
    }

    ENGINE_fillRectangle(25, 33, 34, 24, 0);
    ENGINE_fillRectangle(7, 10, 114, 16, 0);

    lpReloadTitle[7] = (lMaxCount - aCount) + '0';
    if (aShootNow == 0) {
        ENGINE_drawString(63 - 10 * 11 / 2, 10, lpReloadTitle, 1);
        ENGINE_drawBitmapByIndex(25, 33, EII_RELOAD_ARROW);
    } else {
        ENGINE_drawString(63 - 10 * 6 / 2, 10, "SHOOT!", 1);
        ENGINE_drawBitmapByIndex(25, 33, EII_DEAGLE);
    }

    if (aType == 1) {
        for (i = 0; i < aCount; i++) {
            ENGINE_drawBitmapByIndex(68 + i * 15, 28, EII_MAGAZINE_INVERT);
        }
        for (; i < lMaxCount; i++) {
            ENGINE_drawBitmapByIndex(68 + i * 15, 28, EII_MAGAZINE_EMPTY);
        }
    } else if (aType == 2) {
        DISPLAY_bullets(60, 32, ENGINE_getAmmo(), aCount);
    } else if (aType == 3) {
        /*bullets*/

        ENGINE_fillRectangle(68, 28, 50, 8, 0);
        for (i = 0; i < ENGINE_getAmmo(); i++) {
            DISPLAY_drawBullet(68 + i * 6, 28, 2);
        }
        for (; i < 7; i++) {
            DISPLAY_drawBullet(68 + i * 6, 28, 1);
        }
        /*magazines*/
        ENGINE_fillRectangle(68, 38, 55, 20, 0);
        for (i = 0; i < (3 - aCount); i++) {
            ENGINE_drawBitmapByIndex(68 + i * 15, 38, EII_MAGAZINE_SMALL);
        }
        for (; i < lMaxCount; i++) {
            ENGINE_drawBitmapByIndex(68 + i * 15, 38, EII_MAGAZINE_SMALL_EMPTY);
        }
    }
}

void DISPLAY_tutorialWeaponsChange(uint8_t aCount,
                                   uint8_t aWeaponListLength,
                                   uint8_t *apWeaponsList,
                                   uint8_t aSwipe,
                                   uint8_t aArrowsAnimation) {

    uint8_t i = 0;
    tImage *lpItem1;
    tImage *lpItem2;
    tImage *lpItem3;
    uint8_t *lpItemNameList[CS_WEAPONS_ALL_NMBR] = {0};
    tImage *lpItemList[CS_WEAPONS_ALL_NMBR] = {0};
    uint8_t lItemNameLength = 0;
    int16_t lX1, lX2, lX3;
    uint8_t lY1, lY2, lY3;
    int16_t lDist1, lDist2, lDist3;
    uint8_t lItemCount = aWeaponListLength;
    uint8_t lWeaponsCount = aWeaponListLength;
    uint8_t lCirclesX;
    uint8_t lWeaponListIndex;
    const uint8_t lcPixels = 10;
    const uint8_t lcMiddleX = 64;
    const uint8_t lcMiddleY = 35;
    const uint8_t lcCirclesStep = 12;
    const uint8_t lcCircleRadius = 4;
    const uint8_t lcArrowsX = 100;
    const uint8_t lcArrowsY = 4;

    if (aCount == 0) {
        lWeaponListIndex = aWeaponListLength - 1;
    } else {
        lWeaponListIndex = (aCount - 1) % aWeaponListLength;
        if (aCount > aWeaponListLength + 1) {
            aCount = aWeaponListLength + 1;
        }
    }

    for (i = 0; i < lWeaponsCount; i++) {
        lpItemList[i] = *gpItemList[apWeaponsList[i]];
        lpItemNameList[i] = gpItemNameList[apWeaponsList[i]];
    }

    lpItem1 = lpItemList[(lWeaponListIndex - 1 + lItemCount) % lItemCount];
    lpItem2 = lpItemList[lWeaponListIndex];
    lpItem3 = lpItemList[(lWeaponListIndex + 1) % lItemCount];

    lX1 = lcPixels - lpItem1->width;
    lX2 = lcMiddleX - lpItem2->width / 2;
    lX3 = DISPLAY_WIDTH - lcPixels;
    lY1 = lcMiddleY - lpItem1->height / 2;
    lY2 = lcMiddleY - lpItem2->height / 2;
    lY3 = lcMiddleY - lpItem3->height / 2;

    while (lpItemNameList[lWeaponListIndex][lItemNameLength] != 0 && lItemNameLength < 6) {
        lItemNameLength++;
    }

    ENGINE_fillRectangle(2, 3, 124, 58, 0);

    if (aSwipe == 0) {
        uint8_t lXName = lcMiddleX;
        uint8_t lXNameLength = lItemNameLength * 11; // 11 is char size on display and 10 is space between anme and price

        lXName = lXName - lXNameLength / 2;
        ENGINE_drawString(lXName, 6, lpItemNameList[lWeaponListIndex], 1);

        ENGINE_drawBitmapByIndex(lX1, lY1, lpItem1Index);
        ENGINE_drawBitmapByIndex(lX2, lY2, lpItem2Index);
        ENGINE_drawBitmapByIndex(lX3, lY3, lpItem3Index);
    } else {
        if (aSwipe < lcPixels) {
            lDist1 = aSwipe;
        } else if (aSwipe < (100 - lcPixels)) {
            lDist1 = 0;
            lX1 = DISPLAY_WIDTH;
        } else {
            lDist1 = aSwipe - 100 + lcPixels;
            lpItem1 = lpItemList[(lWeaponListIndex + 2) % lItemCount];
            lX1 = DISPLAY_WIDTH;
        }

        lDist2 = (lX2 + lpItem2->width - lcPixels) * aSwipe / 100;
        lDist3 = (lX3 + lpItem3->width / 2 - lcMiddleX) * aSwipe / 100;

        /*lDist1 = aSwipe;
        lDist2 = aSwipe;
        lDist3 = aSwipe;*/

        ENGINE_drawBitmapByIndex(lX1 - lDist1, lY1, lpItem1Index);
        ENGINE_drawBitmapByIndex(lX2 - lDist2, lY2, lpItem2Index);
        ENGINE_drawBitmapByIndex(lX3 - lDist3, lY3, lpItem3Index);
    }

    lCirclesX = lcMiddleX - (aWeaponListLength)*lcCirclesStep / 2 - lcCircleRadius;

    /*aCount incremented at the beginning, to count */
    for (i = 0; i < aCount; i++) {
        ENGINE_fillCircle(lCirclesX + i * lcCirclesStep, 55, 3, 1);
    }
    for (; i < aWeaponListLength + 1; i++) {
        ENGINE_drawCircle(lCirclesX + i * lcCirclesStep, 55, 3, 1);
    }

    /*animated arrows to indicate switch to next weapon*/
    switch (aArrowsAnimation) {
    case 0:
        break;
    case 3:
        ENGINE_drawBitmapByIndex(lcArrowsX + 14, lcArrowsY, EII_ARROW2);
    case 2:
        ENGINE_drawBitmapByIndex(lcArrowsX + 7, lcArrowsY, EII_ARROW2);
    case 1:
        ENGINE_drawBitmapByIndex(lcArrowsX, lcArrowsY, EII_ARROW2);
        break;
    default:
        break;
    }
}

void DISPLAY_tutorialWaiting(uint8_t aPercentage) {
    uint8_t i = 0;

    if (aPercentage > 100) {
        aPercentage = 100;
    }

    ENGINE_drawBitmapByIndex(50, 3, EII_CHECKED);
    ENGINE_drawString(63 - 12 * 3, 29, "YOU ARE READY", 0);
    ENGINE_drawLine(2, 39, 126, 39, 1);
    ENGINE_drawString(63 - 11 * 3, 54, "PLEASE WAIT", 0);
    for (i = 0; i < aPercentage / 10; i++) {
        ENGINE_drawBitmapByIndex(23 + i * 8, 41, EII_FIGURE);
    }

    for (; i < 10; i++) {
        ENGINE_clearBItmapByIndex(23 + i * 8, 41, EII_FIGURE);
    }
}

void DISPLAY_tutorialCongratulation(void) {
    uint8_t aValue = ENGINE_generateRandomNumber(GGT_CONGRAT_NMBR - 1);
    uint8_t lTextLength = strlen(gpCongratulationsList[aValue]);

    ENGINE_clearDisplayBuffer();
    DISPLAY_initLayout(1);

    ENGINE_drawString(63 - lTextLength * 11 / 2, 24, gpCongratulationsList[aValue], 1);
}
