rm champion.cor
rm champion1.cor
./asm champion.s
mv champion.s champion1.s
../ressources/asm champion1.s
mv champion1.s champion.s
hexdump champion1.cor
echo ------------------------------------
hexdump champion.cor
