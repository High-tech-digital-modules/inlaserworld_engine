void ACHIEVEMENTS_customMessageBonusKill(uint8_t *apData, uint8_t aLength,
		uint8_t aDevice) {
  if(aLength == 4 && aDevice == 0){
    if(apData[0] == 'a' && apData[1] == 'c' && apData[2] == 'v'){
      if(apData[3] == 2){
        ENGINE_playSound(sfxDoubleKill);
      } else if(apData[3] > 2){
        ENGINE_playSound(sfxMonsterKill);
      }
    }
  }
}
