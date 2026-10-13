#!/bin/bash

ROOT_PATH=$(pwd | grep -o ".*/inlaserworld_engine")



FINAL_PATH="$ROOT_PATH/plugins"
# Check if the first command-line argument ($1) is provided
if [ -n "$1" ]; then
    FINAL_PATH="$FINAL_PATH/$1"
fi
cd "$ROOT_PATH" || exit 1

build_target() {
    local target_path="$1"
    for buildPath in $(find "$(dirname "$target_path")" -name Makefile); do
        if [[ "$(dirname "$buildPath")" == *-o ]]; then
            make -C "$(dirname "$buildPath")" -j$(($(nproc) - 2)) || exit 1
        fi
    done
}

# 1. Build libraries first
for path in $(find "$FINAL_PATH" -name BUILD.mk); do
    if grep -F -q 'LIB_NAME=lib_$(GAME_TEMPLATE_ID_).a' "$path"; then
        build_target "$path"
    fi
done

# 2. Build remaining plugins
for path in $(find "$FINAL_PATH" -name BUILD.mk); do
    if ! grep -F -q 'LIB_NAME=lib_$(GAME_TEMPLATE_ID_).a' "$path"; then
        build_target "$path"
    fi
done
