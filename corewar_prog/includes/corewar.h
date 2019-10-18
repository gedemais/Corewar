/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/18 16:26:47 by gedemais         ###   ########.fr       */
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

//STRUCTURES ET UNION

enum						e_arg_type
{
	TYPE_NONE,
	TYPE_DIR4,
	TYPE_DIR2,
	TYPE_IND,
	TYPE_REG,
	TYPE_MAX
};

typedef union u_type		t_type;

union			u_type
{
	int			direct;
	short		direct2;
	short		indirect;
	int			registre;
};

typedef struct s_process	t_process;

struct			s_process
{
	t_process	*prev;
	t_process	*next;
	int			*r;
	int			wait_cycle;
	int			carry;
	uint32_t	padding : 20;
	uint16_t	pc : 12;
	char		op_code;
};

typedef struct s_instruct	t_instruct;

struct			s_instruct
{
	t_instruct	*prev;
	t_instruct	*next;
	t_process	*process;
	t_type		arg[MAX_ARG_FUNC];
	char		type[MAX_ARG_FUNC];
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
	char			padding[6];
	bool			dead;
	char			pad2[4];
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

/////////////////////PROTOTYPES/////////////////////

//Ajouter a la lib

unsigned int	get_name_len(char *name);
int				hex_convert(char a, char b, char c, char d);
char			*merge_args(int ac, char **av);
int				rev_bits(int num);

//Parsing et utils

int				check_id(t_env *env);
int				error(char *error_msg, char *file);
long long int	find_id(t_env *env, unsigned int nb_p);
void			free_env(t_env *env);
int				get_opt_champ(t_env *env, char *arg);
int				loader(t_env *env, t_player *player, char *arg, int len);

//Corewar loop

int				add_instruction(t_env *env, int num_player);
int				check_instruct(t_env *env, t_process *process);
int				check_live(t_env *env);
int				check_op(t_env *env, t_process *process);
int				create_first_process(t_env *env);
int				cw_loop(t_env *env);
int				cycle_run(t_env *env, curr_cycle);
void			init_arena(t_env *env);
int				load_op(t_env *env, t_process *process);

//Tableau de statique

bool			carry_flag(char c);
int				*convert_instruction(char c);
bool			direct_size(char c);
bool			encoding_byte(char c);
int				nb_arg(char c);
int				wait_cycle(char c);

//Gestion des queues

t_instruct		*new_instruct(t_env *env, t_process *process);
t_process		*new_lst(t_env *env, int id, uint16_t pc);
t_instruct		*push_instruct(t_env *env, t_instruct *instruct);
t_process		*push_lst(t_env *env, t_process *process, int id, uint16_t pc);
t_instruct		*pop_instruct(t_instruct *instruct, t_instruct *tmp, t_instruct *tmp2);
t_process		*pop_lst(t_process *process, t_process *tmp,t_process *tmp2);

//TESTS PROTO

void			aff_env(t_env *env, bool all);
void			aff_player(t_player *player);
void			aff_process(t_process *process);
void			test_convert_instruction(void);
void			test_cw_loop(void);
void			test_get_opt_champ_loader(char *arg);
void			test_loader(void);
void			test_lst(void);
void			test_system(void);

//OP_FONCTION

int				live(t_env *env, t_instruct *inst);
int				ld(t_env *env, t_instruct *inst);
int				st(t_env *env, t_instruct *inst);
int				add(t_env *env, t_instruct *inst);
int				sub(t_env *env, t_instruct *inst);
int				and(t_env *env, t_instruct *inst);
int				xor(t_env *env, t_instruct *inst);
int				or(t_env *env, t_instruct *inst);
int				zjmp(t_env *env, t_instruct *inst);
int				ldi(t_env *env, t_instruct *inst);
int				sti(t_env *env, t_instruct *inst);
int				forky(t_env *env, t_instruct *inst);
int				lld(t_env *env, t_instruct *inst);
int				lldi(t_env *env, t_instruct *inst);
int				lfork(t_env *env, t_instruct *inst);
int				aff(t_env *env, t_instruct *inst);

#endif
