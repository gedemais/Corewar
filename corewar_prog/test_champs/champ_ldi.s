.name "test corewar"
.comment "t'as pete ?"

label:	ldi r1, %42, r2
	ldi %:label, r2, r3
	ldi %-10, r3, r4
	ldi 10, %12, r5
	ldi 1024, %12, r5
	ldi %1024, %12, r5
