.name "le_truc_qui_prouve_que"
.comment "Ce programme montre comment les processus ne regardent pas la
prochaine instruction juste apres avoir fini lactuelle mais apres que tous
les autres aient fini les leurs, soit au debut du prochain tour."

# 09 00 0e 00
start:
	ld %150998528, r9
	and r1,%0,r1
	fork %:second

# Where the first process does magic
first:
	st r9, :overwrite

# Where the second proces does magic
second:
	st r9, r8

# What will be changed
overwrite:
	fork %:start
