#!/bin/bash

ARG1="corewar"
ARG2="../resources/corewar"
RESULT="result.txt"
TEST1="test1.txt"
TEST2="test2.txt"

champa[0]="-a ../resources/champion_compilees/helltrain.cor"
champa[1]="-a ../resources/champion_compilees/maxidef.cor"
champa[2]="-a ../resources/champion_compilees/Gagnant.cor"
champa[3]="-a ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champa[4]="-a ../resources/champion_compilees/bigzork.cor"
champa[5]="-a ../resources/champion_compilees/ex.cor"
champa[6]="-a ../resources/champion_compilees/fluttershy.cor"
champa[7]="-a ../resources/champion_compilees/jumper.cor"
champa[8]="-a ../resources/champion_compilees/mortel.cor"
champa[9]="-a ../resources/champion_compilees/slider2.cor"
champa[10]="-a ../resources/champion_compilees/toto.cor"
champa[11]="-a ../resources/champion_compilees/turtle.cor"
champa[12]="-a ../resources/champion_compilees/zork.cor"

champv[0]="-v 31 ../resources/champion_compilees/helltrain.cor"
champv[1]="-v 31 ../resources/champion_compilees/maxidef.cor"
champv[2]="-v 31 ../resources/champion_compilees/Gagnant.cor"
champv[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champv[4]="-v 31 ../resources/champion_compilees/bigzork.cor"
champv[5]="-v 31 ../resources/champion_compilees/ex.cor"
champv[6]="-v 31 ../resources/champion_compilees/fluttershy.cor"
champv[7]="-v 31 ../resources/champion_compilees/jumper.cor"
champv[8]="-v 31 ../resources/champion_compilees/mortel.cor"
champv[9]="-v 31 ../resources/champion_compilees/slider2.cor"
champv[10]="-v 31 ../resources/champion_compilees/toto.cor"
champv[11]="-v 31 ../resources/champion_compilees/turtle.cor"
champv[12]="-v 31 ../resources/champion_compilees/zork.cor"

champd[0]="-d 1 ../resources/champion_compilees/helltrain.cor"
champd[1]="-d 1 ../resources/champion_compilees/maxidef.cor"
champd[2]="-d 1 ../resources/champion_compilees/Gagnant.cor"
champd[3]="-d 1 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champd[4]="-d 1 ../resources/champion_compilees/bigzork.cor"
champd[5]="-d 1 ../resources/champion_compilees/ex.cor"
champd[6]="-d 1 ../resources/champion_compilees/fluttershy.cor"
champd[7]="-d 1 ../resources/champion_compilees/jumper.cor"
champd[8]="-d 1 ../resources/champion_compilees/mortel.cor"
champd[9]="-d 1 ../resources/champion_compilees/slider2.cor"
champd[10]="-d 1 ../resources/champion_compilees/toto.cor"
champd[11]="-d 1 ../resources/champion_compilees/turtle.cor"
champd[12]="-d 1 ../resources/champion_compilees/zork.cor"

champdd[0]="-d 100 ../resources/champion_compilees/helltrain.cor"
champdd[1]="-d 100 ../resources/champion_compilees/maxidef.cor"
champdd[2]="-d 100 ../resources/champion_compilees/Gagnant.cor"
champdd[3]="-d 100 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champdd[4]="-d 100 ../resources/champion_compilees/bigzork.cor"
champdd[5]="-d 100 ../resources/champion_compilees/ex.cor"
champdd[6]="-d 100 ../resources/champion_compilees/fluttershy.cor"
champdd[7]="-d 100 ../resources/champion_compilees/jumper.cor"
champdd[8]="-d 100 ../resources/champion_compilees/mortel.cor"
champdd[9]="-d 100 ../resources/champion_compilees/slider2.cor"
champdd[10]="-d 100 ../resources/champion_compilees/toto.cor"
champdd[11]="-d 100 ../resources/champion_compilees/turtle.cor"
champdd[12]="-d 100 ../resources/champion_compilees/zork.cor"

champvm[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champvm[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champvm[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champvm[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champvm[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champvm[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champvm[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champvm[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champvm[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champvm[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champvm[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champvm[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champvm[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champdm[0]="-d 1 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champdm[1]="-d 1 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champdm[2]="-d 1 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champdm[3]="-d 1 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champdm[4]="-d 1 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champdm[5]="-d 1 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champdm[6]="-d 1 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champdm[7]="-d 1 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champdm[8]="-d 1 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champdm[9]="-d 1 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champdm[10]="-d 1 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champdm[11]="-d 1 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champdm[12]="-d 1 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champddm[0]="-d 100 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champddm[1]="-d 100 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champddm[2]="-d 100 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/mortel.cor"
champddm[3]="-d 100 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champddm[4]="-d 100 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champddm[5]="-d 100 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champddm[6]="-d 100 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champddm[7]="-d 100 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champddm[8]="-d 100 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champddm[9]="-d 100 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champddm[10]="-d 100 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champddm[11]="-d 100 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champddm[12]="-d 100 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champam[0]="-a ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champam[1]="-a ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/fluttershy.cor"
champam[2]="-a ../resources/champion_compilees/gagnant.cor ../resources/champion_compilees/mortel.cor"
champam[3]="-a ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/jumper.cor"
champam[4]="-a ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/zork.cor"
champam[5]="-a ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champam[6]="-a ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/toto.cor"
champam[7]="-a ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/slider2.cor"
champam[8]="-a ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/Gagnant.cor"
champam[9]="-a ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/turtle.cor"
champam[10]="-a ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champam[11]="-a ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/turtle.cor"
champam[12]="-a ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champvmm[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/helltrain.cor"
champvmm[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/maxidef.cor"
champvmm[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/Gagnant.cor"
champvmm[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor"
champvmm[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/bigzork.cor"
champvmm[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/ex.cor"
champvmm[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/fluttershy.cor"
champvmm[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/jumper.cor"
champvmm[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/mortel.cor"
champvmm[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/slider2.cor"
champvmm[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/toto.cor ../resources/champion_compilees/toto.cor ../resources/champion_compilees/toto.cor"
champvmm[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/turtle.cor"
champvmm[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/zork.cor"

champvmmm[0]="-v 31 ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/zork.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor"
champvmmm[1]="-v 31 ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/fluttershy.cor"
champvmmm[2]="-v 31 ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/slider2.cor"
champvmmm[3]="-v 31 ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/mortel.cor"
champvmmm[4]="-v 31 ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor"
champvmmm[5]="-v 31 ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor"
champvmmm[6]="-v 31 ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/bigzork.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/toto.cor"
champvmmm[7]="-v 31 ../resources/champion_compilees/jumper.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/helltrain.cor  ../resources/champion_compilees/fluttershy.cor"
champvmmm[8]="-v 31 ../resources/champion_compilees/mortel.cor ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/maxidef.cor"
champvmmm[9]="-v 31 ../resources/champion_compilees/slider2.cor ../resources/champion_compilees/helltrain.cor  ../resources/champion_compilees/fluttershy.cor ../resources/champion_compilees/bigzork.cor"
champvmmm[10]="-v 31 ../resources/champion_compilees/toto.cor ../resources/champion_compilees/maxidef.cor ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor"
champvmmm[11]="-v 31 ../resources/champion_compilees/turtle.cor ../resources/champion_compilees/Gagnant.cor ../resources/champion_compilees/ex.cor ../resources/champion_compilees/jumper.cor"
champvmmm[12]="-v 31 ../resources/champion_compilees/zork.cor ../resources/champion_compilees/Octobre_Rouge_V4.2.cor ../resources/champion_compilees/helltrain.cor ../resources/champion_compilees/slider2.cor"

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
echo 'TEST -v 31'
for i in ${!champv[@]}; do
echo ${name[i]}
./corewar ${champv[i]} > $TEST1
./$ARG2 ${champv[i]} > $TEST2
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
for i in ${!champa[@]}; do
echo ${name[i]}
./corewar ${champa[i]} > $TEST1
./$ARG2 ${champa[i]} > $TEST2
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
for i in ${!champd[@]}; do
echo ${name[i]}
./corewar ${champd[i]} > $TEST1
./$ARG2 ${champd[i]} > $TEST2
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
for i in ${!champdd[@]}; do
echo ${name[i]}
./corewar ${champdd[i]} > $TEST1
./$ARG2 ${champdd[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -v 31 multiplayer1'
for i in ${!champvm[@]}; do
echo ${name[i]}
./corewar ${champvm[i]} > $TEST1
./$ARG2 ${champvm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -v 31 multiplayer2'
for i in ${!champvmm[@]}; do
echo ${name[i]}
./corewar ${champvmm[i]} > $TEST1
./$ARG2 ${champvmm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -v 31 multiplayer3'
for i in ${!champvmmm[@]}; do
echo ${name[i]}
./corewar ${champvmmm[i]} > $TEST1
./$ARG2 ${champvmmm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -a multiplayer'
for i in ${!champam[@]}; do
echo ${name[i]}
./corewar ${champam[i]} > $TEST1
./$ARG2 ${champam[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -d 1 multiplayer'
for i in ${!champdm[@]}; do
echo ${name[i]}
./corewar ${champdm[i]} > $TEST1
./$ARG2 ${champdm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'

echo 'TEST -d 100 multiplayer'
for i in ${!champddm[@]}; do
echo ${name[i]}
./corewar ${champddm[i]} > $TEST1
./$ARG2 ${champddm[i]} > $TEST2
cmp -b $TEST1 $TEST2 > $RESULT
cat $RESULT
if [ -s "$RESULT" ] ; then
	echo -e '\033[5;31;40m KO \033[0m'
else
	echo -e '\033[5;32;40m OK \033[0m'
fi
done
echo '/////////////////////////////////////////////////////////////////////////'
