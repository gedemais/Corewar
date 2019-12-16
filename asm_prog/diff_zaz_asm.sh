#!/bin/bash

# Copying the corresponding champ
./asm $1
hexdump *.cor > mine
./zaz_asm $1
hexdump *.cor > zaz
diff mine zaz
