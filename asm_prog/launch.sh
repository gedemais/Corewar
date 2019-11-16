rm test.cor
rm test1.cor
./asm test.s
mv test.s test1.s
../ressources/asm test1.s
mv test1.s test.s
hexdump test1.cor
echo ------------------------------------
hexdump test.cor
