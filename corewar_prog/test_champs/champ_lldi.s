.name "test corewar"
.comment "t'as pete ?"

label:	lldi r1, %42, r2
	lldi %:label, r2, r3
	lldi %-10, r3, r4
	lldi 1024, %12, r5
	lldi %1024, %12, r5
