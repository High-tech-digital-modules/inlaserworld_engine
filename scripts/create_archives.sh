#!/bin/bash

mkdir -p ./output

for path in plugins/*/ ; do
	dir=$(basename "$path")
	cd "$path" || exit 1
	tar czf "../../output/$dir.inlaserworld" .
	echo $dir
	cd - || exit 1
done
