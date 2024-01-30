#!/bin/bash

ROOT_PATH=$(pwd | grep -o ".*/inlaserworld_engine")



FINAL_PATH="$ROOT_PATH/plugins"
# Check if the first command-line argument ($1) is provided
if [ -n "$1" ]; then
    FINAL_PATH="$FINAL_PATH/$1"
else
    echo "For transpile I need name of plugin"
    exit 1
fi
cd "$ROOT_PATH" || exit 1

if [ -e "$FINAL_PATH/Main.jsx" ]; then
  echo "There is no Main.jsx so transpile is not done"
  exit 1
fi

FINAL_PATH="$FINAL_PATH/webresult"

echo "" > "$FINAL_PATH/main.js"

find "$FINAL_PATH/extra" -type f -name '*.jsx' | while read -r file; do
  # Read the content of the current extra file
  sed '/^import/d; s/export default //g; s/export //g' "$file" >> "$FINAL_PATH"/main.js
  echo "" >> "$FINAL_PATH"/main.js
done

sed '/^import/d' "$FINAL_PATH/Main.jsx" >> "$FINAL_PATH"/main.js