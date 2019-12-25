.name		"Octobre Rouge V4.2"
.comment	"And the winner is ..."

xxx:		live	%42
		fork	%:torp
		lfork	%:torp
		zjmp	%:xxx
	
zork:		live	%42
		fork	%:zork2
		lfork	%:zork2
		st	r1,13
		ld	%0,r15
zork_:		live	%42
		zjmp	%-5
		
zork2:		live	%42
		fork	%:zork3
		lfork	%:zork3
		st	r1,13
		ld	%0,r15
zork2_:		live	%42
		zjmp	%-5

zork3:		live	%42
		fork	%:zork4
		lfork	%:zork4
		st	r1,13
		ld	%0,r15
zork3_:		live	%42
		zjmp	%-5

zork4:		live	%42
		fork	%:zork
		lfork	%:zork
		st	r1,13
		ld	%0,r15
zork4_:		live	%42
		zjmp	%-5		
			
back_wall:      live	%42	
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		ld	%0,r15
		zjmp	%:back_wall

torp:		live	%42
		fork	%:torp1
		lfork	%:torp1
		live	%42
		fork	%:torp2
		lfork	%:torp2
		live	%42
		fork	%:torp3
		lfork	%:torp3
		ld	%57672448,r3		#03 70 03 00
		ld	%318992390,r6		#13 03 70 06
		ld	%0,r15
		zjmp	%:launch
	
torp1:		live	%42
		fork	%:torp
		lfork	%:torp
		live	%42
		fork	%:zork
		lfork	%:zork
		ld	%251883526,r3		#0F 03 70 06
		ld	%386101254,r6		#17 03 70 06
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

torp2:		live	%42
		fork	%:back_wall
		lfork	%:back_wall
		ld	%4294902082,r3		#FF FF 01 42
		ld	%436432902,r6		#1A 03 70 06
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

torp3:		st	r1,r3	
		ld	%251883526,r6
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

launch:	st	r3,15
	st	r6,-1
launc_:	live	%42







