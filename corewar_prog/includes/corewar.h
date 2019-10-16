/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/15 17:56:17 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "../../libft/libft.h"
# include "define.h"
# include "op.h"
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>

//STRUCTURES

typedef struct s_process	t_process;

struct			s_process
{
	t_process	*prev;
	t_process	*next;
	int			*r; // REG_NUMBER malloc a REG_SIZE
	uint16_t	pc : 12;
	uint32_t	_pad : 20;
	int			carry;
};

typedef struct		s_player
{
	char			comment[COMMENT_LENGTH + 1];
	char			champ[CHAMP_MAX_SIZE];
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		pad;
	uint32_t		magic;
	uint32_t		siz;
	long long int	id;
	unsigned int	cycle_to_process;
	unsigned int	first_pc;
	bool			dead;
	char			_pad[7];
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_process		*queue_process;
	t_player		player[MAX_PLAYERS];
	char			arena[MEM_SIZE];
	unsigned int	nb_lives[MAX_PLAYERS];
	long long int	dump;
	unsigned int	nb_players;
	unsigned int	live_tot;
	int				cycle_to_die;
	char			_pad[4];
}					t_env;

//PROTOTYPES

void			free_env(t_env *env);
int				get_opt_champ(t_env *env, char *arg);
unsigned int	get_name_len(char *name);
int				loader(t_env *env, t_player *player, char *arg, int len);
char			*merge_args(int ac, char **av);
void			print_test(t_env *env);
int				error(char *error_msg, char *file);
int				check_live(t_env *env);
void			init_arena(t_env *env);
int				process_cycle(t_env *env);
int				cw_loop(t_env *env);
t_process		*new_lst(t_env *env, unsigned int num_pl, uint16_t pc);
t_process		*push_lst(t_env *env, t_process *process, unsigned int num_pl,
		uint16_t pc);
t_process		*pop_lst(t_process *process);
int				reverse_bytes(t_player *player);
void			*convert_instruction(char c, t_env *env);
bool			encoding_byte(char c);
bool			carry_flag(char c);
int				nb_arg(char c);
int				hex_convert(char a, char b, char c, char d);

//TESTS PROTO

void			aff_env(t_env *env, bool all);
void			aff_player(t_player *player);
void			aff_process(t_process *process);
void			test_lst(void);
void			test_loader(void);
void			test_get_opt_champ(void);
void			test_convert_instruction(void);
void			test_cw_loop(void);
void			test_system(void);

//OP_FONCTION

int				live(int direct);
int				ld(int indirect, int direct_reg);
int				st(int reg, int indirect_reg);
int				add(int reg, int reg2, int reg3);
int				sub(int reg, int reg2, int reg3);
int				and(int reg_in_direct, int reg2_in_direct, int reg3);
int				xor(int reg_in_direct, int reg2_in_direct, int reg3);
int				or(int reg_in_direct, int reg2_in_direct, int reg3);
int				zjmp(int direct);
int				ldi(int reg_in_direct, int in_direct, int reg);
int				sti(int reg, int reg_in_direct, int reg_direct);
int				forky(int direct);
int				lld(int in_direct, int reg);
int				lldl(int reg_in_direct, int reg_direct, int reg);
int				lfork(int direct);
int				aff(int reg);

#endif
