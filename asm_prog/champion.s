.name "comment"
.comment "bonjour"

label1:	lld %1, r1
		live %1
		zjmp %:label1

label12: zjmp %:label1
