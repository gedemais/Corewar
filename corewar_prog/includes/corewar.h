/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/17 21:22:36 by moguy            ###   ########.fr       */
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

typedef union u_type		t_type;

union			u_type
{
	int			direct;
	short		direct2;
	short		indirect;
	char		registre;
};

typedef struct s_process	t_process;

struct			s_process
{
	t_process	*prev;
	t_process	*next;
	int			*r;
	int			wait_cycle;
	int			carry;
	uint32_t	_pad : 20;
	uint16_t	pc : 12;
};

typedef struct s_instruct	t_instruc;

struct			s_instruct
{
	t_instruct	*prev;
	t_instruct	*next;
	t_process	*process;
	t_type		arg[3];
	char		op_code;
};

typedef struct		s_player
{
	char			comment[COMMENT_LENGTH + 1];
	char			champ[CHAMP_MAX_SIZE];
	char			prog_name[PROG_NAME_LENGTH + 1];
	long long int	id;
	unsigned int	first_pc;
	uint32_t		pad;
	uint32_t		magic;
	uint32_t		siz;
	char			_pad[6];
	bool			dead;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_instruct		*instruct;
	t_player		player[MAX_PLAYERS];
	unsigned int	nb_lives[MAX_PLAYERS];
	char			arena[MEM_SIZE];
	long long int	dump;
	int				cycle_to_die;
	unsigned int	live_tot;
	unsigned int	nb_players;
	char			_pad[4];
}					t_env;

//PROTOTYPES

void			free_env(t_env *env);
int				get_opt_champ(t_env *env, char *arg);
unsigned int	get_name_len(char *name);
int				loader(t_env *env, t_player *player, char *arg, int len);
char			*merge_args(int ac, char **av);
int				error(char *error_msg, char *file);
int				check_live(t_env *env);
int				check_id(t_env *env);
int				check_cycle(t_env *env, t_process *process, int cur_cycle);
int				add_instruction(t_env *env, int num_player);
long long int	find_id(t_env *env, unsigned int nb_p);
void			init_arena(t_env *env);
int				cycle_run(t_env *env, curr_cycle);
int				cw_loop(t_env *env);
int				create_first_process(t_env *env);
t_process		*new_lst(t_env *env, int id, uint16_t pc);
t_process		*push_lst(t_env *env, t_process *process, int id, uint16_t pc);
t_process		*pop_lst(t_process *process, t_process *tmp,t_process *tmp2);
t_instruct		*pop_instruct(t_instruct *instruct, t_instruct *tmp, t_instruct *tmp2);
t_instruct		*push_instruct(t_env *env, t_instruct *instruct,
		unsigned int num_pl, uint16_t pc);
t_instruct		*new_instruct(t_env *env, t_process *process, t_type *arg);
int				*convert_instruction(char c);
bool			encoding_byte(char c);
bool			carry_flag(char c);
int				nb_arg(char c);
int				hex_convert(char a, char b, char c, char d);
int				rev_bits(int num);

//TESTS PROTO

void			aff_env(t_env *env, bool all);
void			aff_player(t_player *player);
void			aff_process(t_process *process);
void			test_lst(void);
void			test_loader(void);
void			test_get_opt_champ_loader(char *arg);
void			test_convert_instruction(void);
void			test_cw_loop(void);
void			test_system(void);

//OP_FONCTION

int				live(t_env *env, t_type arg[3], char encoding_byte);
int				ld(t_env *env, t_type arg[3], char encoding_byte);
int				st(t_env *env, t_type arg[3], char encoding_byte);
int				add(t_env *env, t_type arg[3], char encoding_byte);
int				sub(t_env *env, t_type arg[3], char encoding_byte);
int				and(t_env *env, t_type arg[3], char encoding_byte);
int				xor(t_env *env, t_type arg[3], char encoding_byte);
int				or(t_env *env, t_type arg[3], char encoding_byte);
int				zjmp(t_env *env, t_type arg[3], char encoding_byte);
int				ldi(t_env *env, t_type arg[3], char encoding_byte);
int				sti(t_env *env, t_type arg[3], char encoding_byte);
int				forky(t_env *env, t_type arg[3], char encoding_byte);
int				lld(t_env *env, t_type arg[3], char encoding_byte);
int				lldi(t_env *env, t_type arg[3], char encoding_byte);
int				lfork(t_env *env, t_type arg[3], char encoding_byte);
int				aff(t_env *env, t_type arg[3], char encoding_byte);

#endif
