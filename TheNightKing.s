.name "champion_du_siecle"
.comment "faut juste battre zork en vrai..."

l0:	st r1, 6
	live %0
	st r1, 8
	st r1, 16
	fork %:l0
	zjmp %512

l1:	st r1, 0
	ld %1, r5
	zjmp %:l0
