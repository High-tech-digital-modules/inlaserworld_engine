#include <unistd.h>
#ifdef VSCODE
#include "engine_functions.h"
#include "custom_variables_map.h"
#include "sound_set_map.h"
#endif

const char pgLightBroadcastAddress[] = "000000000000000000";
const ColorT gLightColorStandby = {0x50, 0x50, 0x50};
const ColorT gLightColorBlack = {0x00, 0x00, 0x00};

void LIGHT_setColorStandby(void) {
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x5550 ); //stop all operations
  usleep(40000);
/*  ENGINE_lightClearOperationBuffer(pgLightBroadcastAddress);
  ENGINE_lightClearSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 0, gLightColorStandby.red, gLightColorStandby.green, gLightColorStandby.blue, 30, 0 });
  ENGINE_lightAddSequence(pgLightBroadcastAddress, { 0, 1 }, 0b00010101);
  usleep(40000);
  ENGINE_lightSyncOperationBuffer(pgLightBroadcastAddress);
  usleep(40000);
  ENGINE_lightSyncSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x7770 );
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x4440 );*/
  
  ENGINE_lightSetColors(pgLightBroadcastAddress, gLightColorStandby, gLightColorStandby, gLightColorStandby, 0);
}

//set all lights in arena to specific color, enable/disable UV. Color of bonus are black
void LIGHT_setArenaLightsColor(ColorT aColor, uint8_t aUVEnable) {
  /*ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x5005 ); //stop all operations on lights circuit and UV
  usleep(40000);*/
  
  /*
  ENGINE_lightClearOperationBuffer(pgLightBroadcastAddress);
  ENGINE_lightClearSequenceBuffer(pgLightBroadcastAddress, 0b00000011);
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 0, aColor.red, aColor.green, aColor.blue, 10, 0 });
  ENGINE_lightAddSequence(pgLightBroadcastAddress, { 0, 1 }, 0b00010101);
  usleep(40000);
  ENGINE_lightSyncOperationBuffer(pgLightBroadcastAddress);
  usleep(40000);
  ENGINE_lightSyncSequenceBuffer(pgLightBroadcastAddress, 0b00000011);
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x7000 );
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x4000 );*/
  
  ENGINE_lightSetColors(pgLightBroadcastAddress, aColor, aColor, aColor, aUVEnable);
  std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();
  for(DeviceT lModule : lBonusModules){
    ENGINE_lightSetColors(lModule.address, aColor, gLightColorBlack, gLightColorBlack, aUVEnable);
  }
}

void LIGHT_switchOffModule(std::string aAddress) {
  ENGINE_lightStartSequence(aAddress, 0x5555 ); //stop all operations
  usleep(40000);
}

void LIGHT_switchOffAllModules(void) {
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x5555 ); //stop all operations
  usleep(40000);
}