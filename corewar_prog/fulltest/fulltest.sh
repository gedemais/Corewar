#!/bin/bash

ARG1="corewar"
ARG2="../resources/corewar"
RESULT="result.txt"
TEST1="test1.txt"
TEST2="test2.txt"

champo[0]="-v 2 -s 10 -a ../resources/champion_compilees/helltrain.cor"
champo[1]="-v 2 -s 10 -a ../resources/champion_compilees/maxidef.cor"
champo[2]="-v 2 -s 10 -a ../resources/champion_compilees/Gagnant.cor"
champo[3]="-v 2 -s 10 -a ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champo[4]="-v 2 -s 10 -a ../resources/champion_compilees/bigzork.cor"
champo[5]="-v 2 -s 10 -a ../resources/champion_compilees/ex.cor"
champo[6]="-v 2 -s 10 -a ../resources/champion_compilees/fluttershy.cor"
champo[7]="-v 2 -s 10 -a ../resources/champion_compilees/jumper.cor"
champo[8]="-v 2 -s 10 -a ../resources/champion_compilees/mortel.cor"
champo[9]="-v 2 -s 10 -a ../resources/champion_compilees/slider2.cor"
champo[10]="-v 2 -s 10 -a ../resources/champion_compilees/toto.cor"
champo[11]="-v 2 -s 10 -a ../resources/champion_compilees/turtle.cor"
champo[12]="-v 2 -s 10 -a ../resources/champion_compilees/zork.cor"

champss[0]="-v 2 -s 100 ../resources/champion_compilees/helltrain.cor"
champss[1]="-v 2 -s 100 ../resources/champion_compilees/maxidef.cor"
champss[2]="-v 2 -s 100 ../resources/champion_compilees/Gagnant.cor"
champss[3]="-v 2 -s 100 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champss[4]="-v 2 -s 100 ../resources/champion_compilees/bigzork.cor"
champss[5]="-v 2 -s 100 ../resources/champion_compilees/ex.cor"
champss[6]="-v 2 -s 100 ../resources/champion_compilees/fluttershy.cor"
champss[7]="-v 2 -s 100 ../resources/champion_compilees/jumper.cor"
champss[8]="-v 2 -s 100 ../resources/champion_compilees/mortel.cor"
champss[9]="-v 2 -s 100 ../resources/champion_compilees/slider2.cor"
champss[10]="-v 2 -s 100 ../resources/champion_compilees/toto.cor"
champss[11]="-v 2 -s 100 ../resources/champion_compilees/turtle.cor"
champss[12]="-v 2 -s 100 ../resources/champion_compilees/zork.cor"

champs[0]="-v 2 -s 1 ../resources/champion_compilees/helltrain.cor"
champs[1]="-v 2 -s 1 ../resources/champion_compilees/maxidef.cor"
champs[2]="-v 2 -s 1 ../resources/champion_compilees/Gagnant.cor"
champs[3]="-v 2 -s 1 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champs[4]="-v 2 -s 1 ../resources/champion_compilees/bigzork.cor"
champs[5]="-v 2 -s 1 ../resources/champion_compilees/ex.cor"
champs[6]="-v 2 -s 1 ../resources/champion_compilees/fluttershy.cor"
champs[7]="-v 2 -s 1 ../resources/champion_compilees/jumper.cor"
champs[8]="-v 2 -s 1 ../resources/champion_compilees/mortel.cor"
champs[9]="-v 2 -s 1 ../resources/champion_compilees/slider2.cor"
champs[10]="-v 2 -s 1 ../resources/champion_compilees/toto.cor"
champs[11]="-v 2 -s 1 ../resources/champion_compilees/turtle.cor"
champs[12]="-v 2 -s 1 ../resources/champion_compilees/zork.cor"

champsm[0]="-s 1 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champsm[1]="-s 1 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champsm[2]="-s 1 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champsm[3]="-s 1 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champsm[4]="-s 1 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champsm[5]="-s 1 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champsm[6]="-s 1 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champsm[7]="-s 1 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champsm[8]="-s 1 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champsm[9]="-s 1 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champsm[10]="-s 1 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champsm[11]="-s 1 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champsm[12]="-s 1 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champssm[0]="-s 100 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champssm[1]="-s 100 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champssm[2]="-s 100 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champssm[3]="-s 100 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champssm[4]="-s 100 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champssm[5]="-s 100 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champssm[6]="-s 100 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champssm[7]="-s 100 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champssm[8]="-s 100 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champssm[9]="-s 100 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champssm[10]="-s 100 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champssm[11]="-s 100 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champssm[12]="-s 100 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champom[0]="-v 2 -s 10 -a ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor"
champom[1]="-v 2 -s 10 -a ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/fluttershy.cor"
champom[2]="-v 2 -s 10 -a ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/slider2.cor"
champom[3]="-v 2 -s 10 -a ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/mortel.cor"
champom[4]="-v 2 -s 10 -a ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor"
champom[5]="-v 2 -s 10 -a ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor"
champom[6]="-v 2 -s 10 -a ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor"
champom[7]="-v 2 -s 10 -a ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/helltrain.cor  ../resources/champion_compilees/fluttershy.cor"
champom[8]="-v 2 -s 10 -a ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor"
champom[9]="-v 2 -s 10 -a ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/helltrain.cor  ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/bigzork.cor"
champom[10]="-v 2 -s 10 -a ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champom[11]="-v 2 -s 10 -a ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor"
champom[12]="-v 2 -s 10 -a ../resources/champion_compilees/zork.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/slider2.cor"

name[0]="helltrain.cor"
name[1]="maxidef.cor"
name[2]="Gagnant.cor"
name[3]="Octobre_Rouge_V4.2.cor"
name[4]="bigzork.cor"
name[5]="ex.cor"
name[6]="fluttershy.cor"
name[7]="jumper.cor"
name[8]="mortel.cor"
name[9]="slider2.cor"
name[10]="toto.cor"
name[11]="turtle.cor"
name[12]="zork.cor"

make DEBUG=1
echo 'TEST -s 1 push CTRL D for each .cor'
for i in ${!champs[@]}; do
echo ${name[i]}
./corewar ${champs[i]} > $TEST1
./$ARG2 ${champs[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -s 100 push CTRL D for each .cor'
for i in ${!champss[@]}; do
echo ${name[i]}
./corewar ${champss[i]} > $TEST1
./$ARG2 ${champss[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -v 2 -s 10 -a push CTRL D for each .cor'
for i in ${!champo[@]}; do
echo ${name[i]}
./corewar ${champo[i]} > $TEST1
./$ARG2 ${champo[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -s 1 multiplayer push CTRL D for each .cor'
for i in ${!champsm[@]}; do
echo ${name[i]}
./corewar ${champsm[i]} > $TEST1
./$ARG2 ${champsm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -s 100 multiplayer push CTRL D for each .cor'
for i in ${!champssm[@]}; do
echo ${name[i]}
./corewar ${champssm[i]} > $TEST1
./$ARG2 ${champssm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -v 2 -s 10 -a multiplayer push CTRL D for each .cor'
for i in ${!champom[@]}; do
echo ${name[i]}
./corewar ${champom[i]} > $TEST1
./$ARG2 ${champom[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
