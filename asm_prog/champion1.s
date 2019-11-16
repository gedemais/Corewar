.name "comment"
.comment "bonjour"

label1:	lld %1, r1
		live %1
		ld %42, r3
		zjmp %:label1

label12: zjmp %:label1
		ld 42, r7
		ld :label12, r8
		
