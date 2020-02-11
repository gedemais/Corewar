#!/bin/bash

ARG1='corewar'
ARG2="../resources/corewar"
ARG3='../resources/champion_compilees/'
ARG4=' -v 31 '
RESULT="result.txt"
TEST1="test1.txt"
TEST2="test2.txt"

name[0]='helltrain.cor'
name[1]='maxidef.cor'
name[2]='Gagnant.cor'
name[3]='Octobre_Rouge_V4.2.cor'
name[4]='bigzork.cor'
name[5]='ex.cor'
name[6]='fluttershy.cor'
name[7]='jumper.cor'
name[8]='mortel.cor'
name[9]='slider2.cor'
name[10]='toto.cor'
name[11]='turtle.cor'
name[12]='zork.cor'

make DEBUG=1
count=0
i=0
while [ "$i" != 13 ]
do
	j=0
	while [ "$j" != 13 ]
	do
		k=0
		while [ "$k" != 13 ]
		do
			l=0
			while [ "$l" != 13 ]
			do
				echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]} ${name[$l]}" &
				./corewar $ARG4 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} $ARG3${name[$l]} > $TEST1 &
				./$ARG2 $ARG4 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} $ARG3${name[$l]} > $TEST2
				cmp -b $TEST1 $TEST2 > $RESULT &
				cat $RESULT
				if [ -s "$RESULT" ] ; then
					echo -e '\033[5;31;40m KO \033[0m'
				else
					echo -e '\033[5;32;40m OK \033[0m'
				fi
				l=$(($l+1))
				count=$(($count+1))
				echo "Test n$count"
			done
			echo '+++1'
			k=$(($k+1))
		done
		echo '++1'
		j=$(($j+1))
	done
	echo '+1'
	i=$(($i+1))
done
