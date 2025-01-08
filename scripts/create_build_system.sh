#!/bin/bash

ROOT_PATH=$(pwd | grep -o ".*/inlaserworld_engine")

echo "$ROOT_PATH"

for D in "$ROOT_PATH"/plugins/* "$ROOT_PATH"/plugins/inlaser_plugins/*; do
  if [ -f "${D}/description.json" ]; then
    isLibrary=$(jq .isLibrary "${D}/description.json")
    SYNC_PATH="$ROOT_PATH/base/arena/base_plugin"
    [ "$isLibrary" == "true" ] && SYNC_PATH="$ROOT_PATH/base/arena/base_library_plugin"
    cp "$SYNC_PATH"/BUILD.mk\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-linux-d\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-linux-o\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-raspbian-d\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-raspbian-o\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-rasp64-d\
      "${D}/arena/"
    cp -r "$SYNC_PATH"/build-rasp64-o\
      "${D}/arena/"

    SYNC_PATH="$ROOT_PATH/base/chest/STM32F427_main_board_plugin_template"
    [ "$isLibrary" == "true" ] && SYNC_PATH="$ROOT_PATH/base/chest/STM32F427_main_board_plugin_library_template"
    cp "$SYNC_PATH"/BUILD.mk\
      "${D}/chest/"
    [ "$isLibrary" == "false" ] && cp "$SYNC_PATH"/stm32f4_flash.ld\
      "${D}/chest/"
    cp -r "$SYNC_PATH"/build-linux-d\
      "${D}/chest/"
    cp -r "$SYNC_PATH"/build-linux-o\
      "${D}/chest/"
    cp -r "$SYNC_PATH"/build-stm32-d\
      "${D}/chest/"
    cp -r "$SYNC_PATH"/build-stm32-o\
      "${D}/chest/"
  fi
done
