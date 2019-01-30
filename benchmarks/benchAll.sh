#!/bin/bash
for filename in *.js; do
	printf "${filename%.*}: "
    node "$filename"
done