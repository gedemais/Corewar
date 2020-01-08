.name "test for all ops"
.comment "every configuartions"

l1:	live	%42

l2:	ld		%42, r2
	ld		42, r2

l3:	st		r3, r4
	st		r3, 42

l4:	add		r4, r4, r4
	sub		r4, r4, r4

l5:	and		%42, %42, r3
	and		%42, 42, r3
	and		%42, r2, r3
	and		42, %42, r3
	and		42, 42, r3
	and		42, r2, r3

l6:	or		%42, %42, r3
	or		%42, 42, r3
	or		%42, r2, r3
	or		42, %42, r3
	or		42, 42, r3
	or		42, r2, r3

l7:	xor		%42, %42, r3
	xor		%42, 42, r3
	xor		%42, r2, r3
	xor		42, %42, r3
	xor		42, 42, r3
	xor		42, r2, r3

l8:	zjmp	%:l1
	zjmp	%:l2
	zjmp	%:l3
	zjmp	%:l4
	zjmp	%:l5
	zjmp	%:l6
	zjmp	%:l7
	zjmp	%:l8
	zjmp	%:l9
	zjmp	%:l10
	zjmp	%:l11
	zjmp	%:l12
	zjmp	%:l13
	zjmp	%:l14
	zjmp	%:l15

l9:	ldi	%42, %42, r5
	ldi	%42, r4, r5
	ldi	42, %42, r5
	ldi	42, r4, r5
	ldi	r2, %42, r5
	ldi	r2, r4, r5

l10:sti	r3, r4, %42
	sti	r3, r4, r5
	sti	r3, %42, %42
	sti	r3, %42, r5
	sti	r3, 42, %42
	sti	r3, 42, r5

l11:fork	%:l1
	fork	%:l2
	fork	%:l3
	fork	%:l4
	fork	%:l5
	fork	%:l6
	fork	%:l7
	fork	%:l8
	fork	%:l9
	fork	%:l10
	fork	%:l11
	fork	%:l12
	fork	%:l13
	fork	%:l14
	fork	%:l15
	fork	%:l16

l12:lld		%42, r9
	lld		42, r9

l13:lldi	r10, r2, r11
#	lldi	r10, 42, r11
#	lldi	42, 42, r11
	lldi	42, r2, r11
	lldi	r10, r2, r11
	lldi	r10, r2, r11

l14:lfork	%:l1
	lfork	%:l2
	lfork	%:l3
	lfork	%:l4
	lfork	%:l5
	lfork	%:l6
	lfork	%:l7
	lfork	%:l8
	lfork	%:l9
	lfork	%:l10
	lfork	%:l11
	lfork	%:l12
	lfork	%:l13
	lfork	%:l14
	lfork	%:l15

l15:aff r1
