#!/bin/bash

ROOT_PATH=$(pwd | grep -o ".*/inlaserworld_engine")

echo "$ROOT_PATH"

cd "$ROOT_PATH" || exit 1

for path in $(find "$ROOT_PATH/plugins" -name BUILD.mk); do
        for buildPath in $(find $(dirname $path) -name Makefile); do
              if [[ "$(dirname $buildPath)" == *-o ]]; then
                  make -C $(dirname $buildPath) clean || exit 1
              fi
        done
done