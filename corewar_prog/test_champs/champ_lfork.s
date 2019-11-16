.name "test corewar"
.comment "t'as pete ?"

label:	live %1
	lfork %90
	lfork %-90
	lfork %1024
	lfork %-1024
