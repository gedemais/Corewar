#ifndef VM_H
# define VM_H

# define MAX_ARGS 30

typedef struct		s_env
{
	char		arena[4096];
	unsigned int	nb_players;
	char		*files[5];
}			t_env;

#endif
