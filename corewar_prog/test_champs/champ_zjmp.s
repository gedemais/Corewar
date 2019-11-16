.name "test corewar"
.comment "t'as pete ?"

label:	live %1
	live %2
	live %3
	zjmp %:label2
	live %1
        live %2
        live %3

label2:	live %1
	live %2
        live %3
	zjmp %-15
