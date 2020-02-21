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
OPT7=" -v 2 "


name[0]="42.cor"
name[1]="live.cor"
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
name[12]="Backward.cor"
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
name[31]="Gagnant.cor"
name[32]="maxidef.cor"
name[33]="salamahenagalabadoun.cor"
name[34]="slider2.cor"
name[35]="youforkmytralala.cor"

make

count=0
i=0
while [ "$i" != 36 ]
do
	j=0
	while [ "$j" != 36 ]
	do
		echo "test ./corewar -v 31 ${name[$i]} ${name[$j]}"
		./corewar $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} > $TEST1
		./$ARG2 $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} > $TEST2
		cmp -b $TEST1 $TEST2 > $RESULT
		cat $RESULT
		if [ -s "$RESULT" ] ; then
			echo -e '\033[5;31;40m KO \033[0m'
			echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]}" >> error.txt
			echo -e '\033[5;31;40m KO \033[0m\n' >> error.txt
		else
			echo -e '\033[5;32;40m OK \033[0m'
		fi
		k=0
		while [ "$k" != 36 ]
		do
			echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]}"
			./corewar $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} > $TEST1
			./$ARG2 $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} > $TEST2
			cmp -b $TEST1 $TEST2 > $RESULT
			cat $RESULT
			if [ -s "$RESULT" ] ; then
				echo -e '\033[5;31;40m KO \033[0m'
				echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]}" >> error.txt
				echo -e '\033[5;31;40m KO \033[0m\n' >> error.txt
			else
				echo -e '\033[5;32;40m OK \033[0m'
			fi
			l=0
			while [ "$l" != 36 ]
			do
				echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]} ${name[$l]}"
				./corewar $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} $ARG3${name[$l]} > $TEST1
				./$ARG2 $OPT7 $ARG3${name[$i]} $ARG3${name[$j]} $ARG3${name[$k]} $ARG3${name[$l]} > $TEST2
				cmp -b $TEST1 $TEST2 > $RESULT
				cat $RESULT
				if [ -s "$RESULT" ] ; then
					echo -e '\033[5;31;40m KO \033[0m'
					echo "test ./corewar -v 31 ${name[$i]} ${name[$j]} ${name[$k]}" >> error.txt
					echo -e '\033[5;31;40m KO \033[0m\n' >> error.txt
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
