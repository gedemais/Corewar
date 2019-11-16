.name "test corewar"
.comment "t'as pete ?"

label:	live %1
	fork %90
	fork %-90
	fork %1024
	fork %-1024
