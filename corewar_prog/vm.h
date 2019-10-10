#ifndef VM_H
# define VM_H

# define MAX_PLAYERS 4
# define REG_SIZE 4
# define REG_NUMBER 16

typedef struct		s_env
{
	char		arena[4096];
	unsigned int	nb_players;
	char		*files[5];
}			t_env;

#endif
