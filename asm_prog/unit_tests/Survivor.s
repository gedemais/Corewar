.name    "Survivor"
.comment "Invincible"

	live	%1
	fork	%:f1
	zjmp	%:f1

f1:	ld	%4, r2
	zjmp	%:run

run:	xor	r1, r2, r2
l1:	st	r2, 1
	live	%1
	zjmp	%:l1
               
 
	
