#ifdef VSCODE
#include "custom_variables_map.h"
#include "sound_set_map.h"
#include <stdint.h>
#include "engine_def.h"
#endif

volatile uint8_t gvTimeBlinking = 0;
volatile uint16_t gvTimeBlinkingCounter = 0;
volatile uint8_t gvTimeBlinkingLed = 0;

volatile uint8_t gvTimeDeath = 0;
volatile uint16_t gvTimeDeathCounter = 0;

volatile uint8_t gvTimeRevival = 0;
volatile uint16_t gvTimeRevivalCounter = 0;

volatile uint8_t gvTimeBonus = 0;
volatile uint16_t gvTimeBonusCounter = 0;

volatile uint8_t gvTimePulse = 1;
volatile uint16_t gvTimePulseCounter = 0;

volatile uint8_t gvTimeBonusObtainedDelay = 0;
volatile uint16_t gvTimeBonusObtainedDelayCounter = 0;

volatile uint16_t gvLengthBlinking = 20;		//in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;		//in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;		//in 0,01*seconds
volatile uint16_t gvLengthBonus = 3000;		//in 0,01*seconds
volatile uint16_t gvLengthBonusObtainedDelay = 500;		//in 0,01*seconds

//volatile static char new_filename[50];
volatile uint8_t gvBonusObtained = 0;
static const uint8_t cPulseIncrement = 10;
volatile uint16_t gvMineHits = 0;

const uint16_t gcLengthBonusImmortality = 1500; //in 0,01*seconds
const uint16_t gcLengthBonusInvisibility = 3000; //in 0,01*seconds
const uint16_t gcLengthBonusMachineGun = 3000; //in 0,01*seconds

typedef enum{
  bonusNone, 
  bonusMachineGun,
  bonusInvisibility,
  bonusImmortality,
  bonusRecoloration
} bonusType;// gvActualBonus = bonusNone;

volatile static bonusType gvActualBonus = bonusNone;

void bonusMachineGunStop(void) {
  if(gvActualBonus == bonusMachineGun) {
    ENGINE_makeShootContinuousStop();
  }
}

void bonusImmortalityStop(void) {
  if(gvActualBonus == bonusImmortality) {
    ENGINE_setAllModulesDim(100,100);
  }
}

void bonusObtained(uint8_t aBonusType) {
  bonusMachineGunStop();
	bonusImmortalityStop();
  gvActualBonus = aBonusType;
  gvTimeBonusCounter = 0;
  gvTimeBonus = 1;
  switch(gvActualBonus){
    case bonusMachineGun: 
		ENGINE_playSoundFromSoundSet(machine_gun);
		gvLengthBonus = gcLengthBonusMachineGun;
    break;
    case bonusInvisibility: 
		ENGINE_playSoundFromSoundSet(invisibility);
		gvLengthBonus = gcLengthBonusInvisibility;
    break;
    case bonusImmortality: 
		ENGINE_playSoundFromSoundSet(immortality);
		gvLengthBonus = gcLengthBonusImmortality;
    break;
  }
}

/*
static FILE *open_next_file(char *filename) {
    int i = 1;
    bool file_exists = true;
    FILE *fp;

    while (file_exists) {
        snprintf(new_filename, sizeof new_filename, "%s%d", filename, i);
        fp = fopen(new_filename, "r");
        file_exists = (fp != NULL);
        if (fp != NULL) {
            fclose(fp);
        }
        i++;
    }

    fp = fopen(new_filename, "w");
    return fp;
}

void logToFile(char *text) {
  FILE *fp = fopen(new_filename, "a");
  fprintf(fp, text);
  fclose(fp);
}*/

void DEATHMATCH_mainLoop(void) {

}

void DEATHMATCH_timer10ms(void) {
	/*blinking every 200 ms*/
	if (gvTimeBlinking == 1) {
		if (gvTimeBlinkingCounter < gvLengthBlinking)
			gvTimeBlinkingCounter++;
		else {
			gvTimeBlinkingCounter = 1;
			gvTimeBlinkingLed = (gvTimeBlinkingLed + 1) % 2;
		}
	} else {
		gvTimeBlinkingCounter = 0;
		gvTimeBlinkingLed = 1;
	}

	/*death counter*/
	if (gvTimeDeath == 1) {
		if (gvTimeDeathCounter < gvLengthDeath)
			gvTimeDeathCounter++;
		else {
			gvTimeDeath = 0;
			if (ENGINE_getLife() > 0) {
				ENGINE_setGameState(game_state_revival);
			} 
		}
	} else {
		gvTimeDeathCounter = 0;
	}

	/*revival counter*/
	if (gvTimeRevival == 1) {
		if (gvTimeRevivalCounter < gvLengthRevival)
			gvTimeRevivalCounter++;
		else {
			gvTimeRevival = 0;
			ENGINE_setGameState(game_state_alive);
		}
	} else {
		gvTimeRevivalCounter = 0;
	}
	
	/*bonus obtained delay counter*/
	if (gvTimeBonusObtainedDelay == 1) {
		if (gvTimeBonusObtainedDelayCounter < gvLengthBonusObtainedDelay)
			gvTimeBonusObtainedDelayCounter++;
		else {
			gvTimeBonusObtainedDelay = 0;
			gvTimeBonusObtainedDelayCounter = 0;
		}
	} else {
		gvTimeBonusObtainedDelayCounter = 0;
	}
	
	/*bonus counter*/
	if (gvTimeBonus == 1) {
		if (gvTimeBonusCounter < gvLengthBonus)
			gvTimeBonusCounter++;
		else {
			gvTimeBonus = 0;
			bonusMachineGunStop();
			bonusImmortalityStop();
			gvActualBonus = bonusNone;
		}
	} else {
		gvTimeBonusCounter = 0;
	}
	
	/*pulsing counter*/
  if (gvActualBonus == bonusImmortality) {
    if (gvTimePulse == 1) {
	   	if (gvTimePulseCounter < 100-cPulseIncrement)
		    gvTimePulseCounter += cPulseIncrement;
		  else {
		    gvTimePulse = 2;
		    gvTimePulseCounter = 100;
		  }
	  } else if (gvTimePulse == 2) {
		  if (gvTimePulseCounter > cPulseIncrement)
		    gvTimePulseCounter -= cPulseIncrement;
		  else {
		    gvTimePulse = 1;
		    gvTimePulseCounter = 0;
		  }
	  } else {
		  gvTimePulseCounter = 0;
	  }
  } else {
    gvTimePulseCounter = 0;
    gvTimePulse = 1;
  }
}

void DEATHMATCH_pressedTrigger(void) {
	uint8_t lGameState = ENGINE_getGameState();

	if ((lGameState == game_state_alive)
			|| (lGameState == game_state_revival)) {
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			if (ENGINE_getAmmo() > 0) {
			  if(gvActualBonus == bonusMachineGun) {
			    ENGINE_makeShootContinuousStart( 0xFF, 0x00, 1, 0, 100); 
			  } else {
				  ENGINE_makeShoot(0xFF, 0x00); /*use default shot strength, no shot custom info*/
				  ENGINE_decrementAmmo(1);
				  ENGINE_playShoot(0);
			  }
			} else {
				ENGINE_playShoot(1);
			}
		} else {
			ENGINE_playShoot(1);
		}
	} else if (lGameState == game_state_dead) {
		ENGINE_playShoot(1);
	}
}

void DEATHMATCH_releasedTrigger(void) {
  if(gvActualBonus == bonusMachineGun) {
    ENGINE_makeShootContinuousStop();
  }
}

void DEATHMATCH_pressedUserButton(void) {
	ENGINE_toggleLightState();
}

void DEATHMATCH_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
		uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
  uint8_t lGameState = ENGINE_getGameState();

  if (lGameState == game_state_alive){
    if((aHitCode == bonusShotCode) && (aHitCustomInfo != 0)) {
      if(gvTimeBonusObtainedDelay == 1){
        return;
      }
	  gvBonusObtained = 1;
      bonusObtained(aHitCustomInfo);
      gvTimeBonusObtainedDelay = 1;
      ENGINE_setVibrationAccordingHitFlag(9); //weapon vibration
      return;
    }

    if(gvActualBonus == bonusImmortality){
      return;
    }

    if(aHitCode == bonusShotCode){
	  gvMineHits++;
	  ENGINE_setPeriodicInfoByte((gvMineHits >> 8)&0xFF, 0);
	  ENGINE_setPeriodicInfoByte(gvMineHits&0xFF, 1);
    }
  
	ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);

	/*process kill*/
	if (ENGINE_getHealth() == 0) {
		ENGINE_processDeath(aHitCode, aHitFlag);
		ENGINE_sendCustomMessage((uint8_t*)"H", 1, aHitCode);
	}
  }
}

void DEATHMATCH_setModulesState(uint8_t aState, uint8_t aGameState,
		uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t* apModulesState,
		volatile uint8_t* apModulesDim1, volatile uint8_t* apModulesDim2,
		volatile colors_t* apModulesColor1, volatile colors_t* apModulesColor2) {
	uint8_t lMessageTemp = 0;
	uint8_t i = 0;

	if (aState == state_game) {
		if ((aGameState == game_state_starting) && (gvTimeBlinkingLed == 1)) {
			lMessageTemp = LED1(led_basic) | LED2(led_basic);
		} else if (aGameState == game_state_alive) {
			lMessageTemp = LED1(led_basic) | LED2(led_basic);
		} else if (aGameState == game_state_revival) {
			if (gvTimeBlinkingLed == 1)
				lMessageTemp = LED1(led_basic) | LED2(led_special);
			else
				lMessageTemp = LED1(led_basic) | LED2(led_basic);
		}
	} else {

	}

	if (aGameState != game_state_alive) {
		for (i = 0; i < MODULES_NUMBER; i++)
			apModulesState[i] = lMessageTemp;
	} else {
	  if(gvActualBonus == bonusInvisibility) {
	    for (i = 0; i < MODULES_NUMBER; i++)
			  apModulesState[i] = 0;
	  } else if(gvActualBonus == bonusImmortality) {
	    for (i = 0; i < MODULES_NUMBER; i++) {
			  apModulesState[i] = lMessageTemp;
			  apModulesDim1[i] = gvTimePulseCounter;
			  apModulesDim2[i] = gvTimePulseCounter;
	    }
	  } else {
	    ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
	  }
	}

	if(gvBonusObtained == 1){
		gvBonusObtained = 0;
		apModulesState[8] |= VIBRATION(VIBRATION_ON);
	}

	if ((aHitFlag != 0) && (gvTimeBonusObtainedDelay == 0)) { /* && (game_state == game_state_dead))*/
		/*change dim value, send for all chest slaves, not for weapon*/
		if (aGameState == game_state_dead) {
			/*reset dim to 100_*/
			ENGINE_setAllModulesDim(100, 100);
		} else {
			ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
		}
		apModulesState[aHitFlag - 1] |= LED1(
				led_stroboscope) | LED2(led_stroboscope);
		ENGINE_setVibrationAccordingHitFlag(aHitFlag);
	}

	/*backlight of display*/
	if ((aState == state_game) || (aState == state_ending)) {
		apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_special));
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			apModulesState[MODULE_MAIN_BOARD] |= LED2(led_basic);
		} else {
			apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_basic));
		}
	}
}

void DEATHMATCH_changedGameStateToAlive(uint8_t aGameStateLast) {
	//logToFile("Alive");
	gvTimeBlinking = 0;
	if (aGameStateLast == game_state_starting) {
		ENGINE_playSoundFromSoundSet(gameStarting);
	}
}

void DEATHMATCH_changedGameStateToDead(uint8_t aGameStateLast) {
	gvTimeDeath = 1;
	ENGINE_playSoundFromSoundSet(death);
	//logToFile("Death");
}

void DEATHMATCH_changedGameStateToRevival(uint8_t aGameStateLast) {
	gvTimeBlinking = 1;
	gvTimeRevival = 1;
	ENGINE_playSoundFromSoundSet(aliveAgain);
	ENGINE_setHealth(100);
	
	//logToFile("Revival");
}

void DEATHMATCH_changedGameStateToStarting(uint8_t aGameStateLast) {
	gvTimeBlinking = 1;
	//logToFile("Starting");
}

void DEATHMATCH_changedGameStateToEnding(uint8_t aGameStateLast) {
	ENGINE_setAllModulesDim(100, 100);
	ENGINE_setAllModulesState(1, 2, 0);
	//logToFile("Ending");
}

void DEATHMATCH_processCustomMessage(uint8_t* apData, uint16_t aLength,
		uint8_t aDevice) {
  if(aLength == 1) {
    if(apData[0] == (uint8_t)'H') {
      ENGINE_playSound(sfxKillDone);
    }	    
	}
	if(bonusEnabled == 1) {
	  if((apData[0] == (uint8_t)'b') && (aLength == 2)) {
	    bonusObtained(apData[1]);
    }
	}
}

void DEATHMATCH_customInit(volatile colors_t* apModulesColor1,
		volatile colors_t* apModulesColor2, volatile uint8_t* apModulesDim1,
		volatile uint8_t* apModulesDim2, uint8_t* apModulesVibrationStrength,
		volatile uint8_t* apModulesState) {
	gvLengthDeath = ENGINE_getLengthDeath();
	gvLengthRevival = ENGINE_getLengthRevival();
	ENGINE_loadShot(0, sfxShoot);
  	ENGINE_loadShot(1, sfxEmptyShoot);
  	ENGINE_playSoundFromSoundSet(loaded);
  	ENGINE_setShotStrength(shootPower);
  
  	ENGINE_setPeriodicInfoLength(2);
  /*
 	FILE *fp = open_next_file("/tmp/chest_log_");
 	fprintf(fp, "log begin\r\n");   
   	fclose(fp);
	*/
}
