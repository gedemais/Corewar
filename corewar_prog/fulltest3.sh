#!/bin/bash

ARG1="corewar"
ARG2="../resources/corewar"
RESULT="result.txt"
TEST1="test1.txt"
TEST2="test2.txt"

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

champ2p[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor"
champ2p[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor"
champ2p[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/bigzork.cor"
champ2p[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor"
champ2p[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champ2p[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/jumper.cor"
champ2p[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor"
champ2p[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champ2p[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/toto.cor"
champ2p[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/turtle.cor"
champ2p[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/zork.cor"
champ2p[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/helltrain.cor"

champ2p2[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champ2p2[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p2[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/bigzork.cor"
champ2p2[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/ex.cor"
champ2p2[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/fluttershy.cor"
champ2p2[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor"
champ2p2[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/mortel.cor"
champ2p2[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/slider2.cor"
champ2p2[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/toto.cor"
champ2p2[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champ2p2[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/zork.cor"
champ2p2[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/helltrain.cor"
champ2p2[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/maxidef.cor"

champ2p3[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p3[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor"
champ2p3[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/ex.cor"
champ2p3[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/fluttershy.cor"
champ2p3[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/jumper.cor"
champ2p3[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/mortel.cor"
champ2p3[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/slider2.cor"
champ2p3[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/toto.cor"
champ2p3[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/turtle.cor"
champ2p3[9]="-v 31 ../resources/champion_compilees/slider2.cor"
champ2p3[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/helltrain.cor"
champ2p3[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/maxidef.cor"
champ2p3[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/Gagnant.cor"

champ2p4[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/bigzork.cor"
champ2p4[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/ex.cor"
champ2p4[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/fluttershy.cor"
champ2p4[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/jumper.cor"
champ2p4[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/mortel.cor"
champ2p4[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/slider2.cor"
champ2p4[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champ2p4[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/turtle.cor"
champ2p4[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/zork.cor"
champ2p4[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/helltrain.cor"
champ2p4[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor"
champ2p4[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champ2p4[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"

champ2p5[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/ex.cor"
champ2p5[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/fluttershy.cor"
champ2p5[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/jumper.cor"
champ2p5[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/mortel.cor"
champ2p5[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/slider2.cor"
champ2p5[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/toto.cor"
champ2p5[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/turtle.cor"
champ2p5[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/zork.cor"
champ2p5[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor"
champ2p5[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/maxidef.cor"
champ2p5[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/Gagnant.cor"
champ2p5[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p5[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/bigzork.cor"

champ2p6[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/fluttershy.cor"
champ2p6[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/jumper.cor"
champ2p6[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champ2p6[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/slider2.cor"
champ2p6[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/toto.cor"
champ2p6[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/turtle.cor"
champ2p6[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/zork.cor"
champ2p6[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/helltrain.cor"
champ2p6[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/maxidef.cor"
champ2p6[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/Gagnant.cor"
champ2p6[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p6[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/bigzork.cor"
champ2p6[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/ex.cor"

champ2p7[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/jumper.cor"
champ2p7[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/mortel.cor"
champ2p7[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/slider2.cor"
champ2p7[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/toto.cor"
champ2p7[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/turtle.cor"
champ2p7[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/zork.cor"
champ2p7[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/helltrain.cor"
champ2p7[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/maxidef.cor"
champ2p7[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/Gagnant.cor"
champ2p7[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p7[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/bigzork.cor"
champ2p7[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/ex.cor"
champ2p7[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/fluttershy.cor"

champ2p8[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/mortel.cor"
champ2p8[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/slider2.cor"
champ2p8[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor"
champ2p8[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champ2p8[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champ2p8[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/helltrain.cor"
champ2p8[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/maxidef.cor"
champ2p8[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/Gagnant.cor"
champ2p8[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p8[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/bigzork.cor"
champ2p8[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/ex.cor"
champ2p8[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/fluttershy.cor"
champ2p8[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/jumper.cor"

champ2p9[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/slider2.cor"
champ2p9[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/toto.cor"
champ2p9[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/turtle.cor"
champ2p9[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/zork.cor"
champ2p9[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/helltrain.cor"
champ2p9[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/maxidef.cor"
champ2p9[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/Gagnant.cor"
champ2p9[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p9[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/bigzork.cor"
champ2p9[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/ex.cor"
champ2p9[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/fluttershy.cor"
champ2p9[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champ2p9[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/mortel.cor"

champ2p10[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/toto.cor"
champ2p10[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor"
champ2p10[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/zork.cor"
champ2p10[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/helltrain.cor"
champ2p10[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/maxidef.cor"
champ2p10[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/Gagnant.cor"
champ2p10[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p10[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/bigzork.cor"
champ2p10[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/ex.cor"
champ2p10[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/fluttershy.cor"
champ2p10[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/jumper.cor"
champ2p10[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/mortel.cor"
champ2p10[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/slider2.cor"

champ2p11[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/turtle.cor"
champ2p11[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/zork.cor"
champ2p11[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/helltrain.cor"
champ2p11[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/maxidef.cor"
champ2p11[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/Gagnant.cor"
champ2p11[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p11[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/bigzork.cor"
champ2p11[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/ex.cor"
champ2p11[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/fluttershy.cor"
champ2p11[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/jumper.cor"
champ2p11[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/mortel.cor"
champ2p11[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/slider2.cor"
champ2p11[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/toto.cor"

champ2p12[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/zork.cor"
champ2p12[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/helltrain.cor"
champ2p12[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/maxidef.cor"
champ2p12[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/Gagnant.cor"
champ2p12[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p12[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/bigzork.cor"
champ2p12[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/ex.cor"
champ2p12[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/fluttershy.cor"
champ2p12[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/jumper.cor"
champ2p12[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/mortel.cor"
champ2p12[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/slider2.cor"
champ2p12[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/toto.cor"
champ2p12[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/turtle.cor"

champ2p13[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/helltrain.cor"
champ2p13[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/maxidef.cor"
champ2p13[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Gagnant.cor"
champ2p13[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champ2p13[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/bigzork.cor"
champ2p13[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champ2p13[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/fluttershy.cor"
champ2p13[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/jumper.cor"
champ2p13[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/mortel.cor"
champ2p13[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/slider2.cor"
champ2p13[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/toto.cor"
champ2p13[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/turtle.cor"
champ2p13[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

make DEBUG=1
echo 'TEST -v 31 2player'
for i in ${!champ2p[@]}; do
echo ${name[i]}
./corewar ${champ2p[i]} > $TEST1
./$ARG2 ${champ2p[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player2'
for i in ${!champ2p2[@]}; do
echo ${name[i]}
./corewar ${champ2p2[i]} > $TEST1
./$ARG2 ${champ2p2[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player3'
for i in ${!champ2p3[@]}; do
echo ${name[i]}
./corewar ${champ2p3[i]} > $TEST1
./$ARG2 ${champ2p3[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player4'
for i in ${!champ2p4[@]}; do
echo ${name[i]}
./corewar ${champ2p4[i]} > $TEST1
./$ARG2 ${champ2p4[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player5'
for i in ${!champ2p5[@]}; do
echo ${name[i]}
./corewar ${champ2p5[i]} > $TEST1
./$ARG2 ${champ2p5[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player6'
for i in ${!champ2p6[@]}; do
echo ${name[i]}
./corewar ${champ2p6[i]} > $TEST1
./$ARG2 ${champ2p6[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player7'
for i in ${!champ2p7[@]}; do
echo ${name[i]}
./corewar ${champ2p7[i]} > $TEST1
./$ARG2 ${champ2p7[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player8'
for i in ${!champ2p8[@]}; do
echo ${name[i]}
./corewar ${champ2p8[i]} > $TEST1
./$ARG2 ${champ2p8[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player9'
for i in ${!champ2p9[@]}; do
echo ${name[i]}
./corewar ${champ2p9[i]} > $TEST1
./$ARG2 ${champ2p9[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player10'
for i in ${!champ2p10[@]}; do
echo ${name[i]}
./corewar ${champ2p10[i]} > $TEST1
./$ARG2 ${champ2p10[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player11'
for i in ${!champ2p11[@]}; do
echo ${name[i]}
./corewar ${champ2p11[i]} > $TEST1
./$ARG2 ${champ2p11[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player12'
for i in ${!champ2p12[@]}; do
echo ${name[i]}
./corewar ${champ2p12[i]} > $TEST1
./$ARG2 ${champ2p12[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
echo 'TEST -v 31 2player13'
for i in ${!champ2p13[@]}; do
echo ${name[i]}
./corewar ${champ2p13[i]} > $TEST1
./$ARG2 ${champ2p13[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
