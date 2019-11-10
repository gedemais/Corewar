.name "test corewar"
.comment "t'as pete ?"

label:	live %1
        live %2
	live %3
        live %4
	sti r1, %2, %4
	sti r1, %:label, %12
	sti r1, %15, r1
