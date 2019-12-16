.name "nom"
.comment "commentaire"

l0:		sti r1, r2, %42
		ld %42, r3
		zjmp %:l0
		st r4, r1
		zjmp %:l1
		sti r4, %42, %12

l1:		xor r1, :l0, r3
		aff r1
		aff r2
		aff r3
		aff r4
		aff r5
		aff r6
		aff r7
		aff r8
		aff r9
		lldi r1, r2, r3
		zjmp %:l0
		sti r4, %42, %12
		zjmp %:l1
