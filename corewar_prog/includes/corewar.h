/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/13 16:58:07 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "../../libft/libft.h"
# include "define.h"
# include "op.h"
# include <limits.h>
# include <stdio.h>

//STRUCTURES

typedef struct s_process	t_process;

struct						s_process
{
	t_process				*prev;
	t_process				*next;
};

typedef struct		s_player
{
	int				pc[CHAMP_MAX_SIZE];
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			_pad[7];
	int				r[16];
	long long int	id;
	unsigned int	prog_size;
	unsigned int	nb_lives;
}					t_player;

typedef struct		s_env
{
	t_player		player[MAX_PLAYERS];
	char			files[MAX_PLAYERS][CHAMP_MAX_SIZE];
	char			arena[MEM_SIZE];
	long long int	dump;
	unsigned int	cycle_to_die;
	unsigned int	cycle_delta;
	unsigned int	nb_players;
	char			_pad[4];
}					t_env;

//PROTOTYPES

int					get_opt_champ(t_env *env, char *arg);
unsigned int		get_name_len(char *name);
int					loader(t_env *env, char *arg, int len);
char				*merge_args(int ac, char **av);
void				print_test(t_env *env, char *arg);

#endif
