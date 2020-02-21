.name		"Vampire"
.comment	"This champion sucks"

wake_up_from_coffin:
	sti		r1, %:suck, %1
	fork	%:suck

suck:
	live	%1337
	zjmp	%:suck

stand_up:
	ld		%0, r2
	ld		%14764146693, r3

seek_blood:
	st		r3, 5
	zjmp	%:seek_blood
