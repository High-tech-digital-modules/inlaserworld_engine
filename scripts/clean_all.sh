#!/bin/bash

ROOT_PATH=$(pwd | grep -o ".*/inlaserworld_engine")

FINAL_PATH="$ROOT_PATH/plugins"
# Check if the first command-line argument ($1) is provided
if [ -n "$1" ]; then
    FINAL_PATH="$FINAL_PATH/$1"
fi
cd "$ROOT_PATH" || exit 1

for path in $(find $FINAL_PATH -name BUILD.mk); do
        for buildPath in $(find $(dirname $path) -name Makefile); do
              if [[ "$(dirname $buildPath)" == *-o ]]; then
                  make -C $(dirname $buildPath) clean || exit 1
              fi
        done
done