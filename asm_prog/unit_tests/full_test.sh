for i in `ls -1 | grep ".*\.s$"`
do
	echo --------------- $i ------------------
	sh diff_zaz_asm.sh $i
done
