#!/bin/bash

ARG1="corewar"
ARG2="../resources/corewar"
ARG3="champions_geoffrey/"
ARG4="champions_zaz/"
RESULT="result.txt"
TEST1="test1.txt"
TEST2="test2.txt"
OPT1=" -a "
OPT2=" -d 1 "
OPT3=" -d 100 "
OPT4=" -s 1 "
OPT5=" -s 100 "
OPT6=" -v 31 "


name[0]="42.cor"
name[1]="Gagnant.cor"
name[2]="MarineKing.cor"
name[3]="Wall.cor"
name[4]="casimir.cor"
name[5]="doge.cor"
name[6]="gedeon.cor"
name[7]="justin_bee.cor"
name[8]="loose.cor"
name[9]="meowluigi.cor"
name[10]="sam_2.0.cor"
name[11]="terminator.cor"
name[12]="Backward.s"
name[13]="Kappa.cor"
name[14]="Octobre_Rouge_V4.2.cor"
name[15]="_honeybadger.cor"
name[16]="corelol.cor"
name[17]="dubo.cor"
name[18]="jinx.cor"
name[19]="littlepuppy.cor"
name[20]=""
name[21]="mortel.cor"
name[22]="skynet.cor"
name[23]="toto.cor"
name[24]=""
name[25]="Machine-gun.cor"
name[26]="THUNDER.cor"
name[27]="barriere.cor"
name[28]="darksasuke.cor"
name[29]="ex.cor"
name[30]="jumper.cor"
name[31]="live.cor"
name[32]="maxidef.cor"
name[33]="salamahenagalabadoun.cor"
name[34]="slider2.cor"
name[35]="youforkmytralala.cor"

make
echo 'TEST -v 31'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT6 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT6 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -a'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT1 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT1 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -d 1'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT2 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT2 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -d 100'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT3 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT3 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -s 1'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT4 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT4 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -s 100'
for i in ${!name[@]}; do
echo ${name[i]}
./corewar $OPT5 $ARG3${name[i]} > $TEST1
./$ARG2 $OPT5 $ARG3${name[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
