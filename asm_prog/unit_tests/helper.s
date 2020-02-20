.name "mowgli"
.comment "the king of the jungle"

start:
ld		%42, r1
sti		r1, %:lab, %1

lab:
live %0
