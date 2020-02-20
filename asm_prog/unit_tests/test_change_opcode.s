.name "mowgli"
.comment "the king of the jungle"

#start:	sti r1,%:aff,%2
#		ld %1,r2
#		add r1,r2,r1
#		fork %:start
#aff:	aff r1

start:	sti r1, %:bis, %1
		ld %272630272,r2
bis:	live %1
fork:	fork %:start
		live %0
		sti r1, %:live, %1
		and r1,%0,r1
		sti r2,%:fork,%0
live:
		live %1
		zjmp %:live


#Ecrire r1 plutloin
#Incrementer r1
#Faire un fork au debut
#Afficher un truc
