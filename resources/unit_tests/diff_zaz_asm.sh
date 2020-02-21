#!/bin/bash

./asm $1
hexdump *.cor > mine
rm *.cor
./zaz_asm $1
hexdump *.cor > zaz
diff mine zaz
rm mine zaz *.cor
