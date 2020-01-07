#!/bin/bash

# Copying the corresponding champ
valgrind --leak-check=full ./asm $1
hexdump *.cor > mine
rm *.cor
./zaz_asm $1
hexdump *.cor > zaz
diff mine zaz
rm mine zaz *.cor
