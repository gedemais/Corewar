/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 08:29:38 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "define.h"
# include "op.h"
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <stdio.h>

/*
** =============================================================================
** 						OPTIONS
** =============================================================================
*/

typedef enum		e_option
{
	A,
	D,
	N,
	S,
	V
}					t_option;

/*
** =============================================================================
** 						OP_CODES
** =============================================================================
*/

typedef enum		e_op_code
{
	OP_NONE,
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_XOR,
	OP_OR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF,
	OP_MAX
}					t_op_code;

/*
** =============================================================================
** 						REGISTRES
** =============================================================================
*/

typedef enum		e_reg_id
{
	REG_NONE,
	REG_1,
	REG_2,
	REG_3,
	REG_4,
	REG_5,
	REG_6,
	REG_7,
	REG_8,
	REG_9,
	REG_10,
	REG_11,
	REG_12,
	REG_13,
	REG_14,
	REG_15,
	REG_16,
	REG_MAX
}					t_reg_id;

/*
** =============================================================================
** 						PROCESS
** =============================================================================
*/

typedef struct		s_op_arg
{
	unsigned char	type;
	unsigned char	pad[3];
	int32_t			arg;
}					t_op_arg;

typedef struct s_instruct	t_instruct;

struct				s_instruct
{
	t_op_arg		args[MAX_ARGS_NUMBER];
	uint32_t		op;
};

typedef struct s_process	t_process;

struct				s_process
{
	t_process		*next;
	t_instruct		instruct;
	int32_t			r[REG_NUMBER];
	uint32_t		pc : 12;
	uint32_t		tpc : 12;
	char			carry;
	uint32_t		pctmp : 12;
	uint32_t		pad : 20;
	int				alive;
	int				cycle_to_exec;
	int				rank;
};

/*
** =============================================================================
** 						VM AND PLAYERS
** =============================================================================
*/

typedef struct		s_player
{
	char			champ[CHAMP_MAX_SIZE];
	char			com[COMMENT_LENGTH + 1];
	char			name[PROG_NAME_LENGTH + 1];
	char			pad[2][PAD_LENGTH];
	uint32_t		id;
	uint32_t		magic;
	uint32_t		size;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_player		player[MAX_PLAYERS];
	uint8_t			arena[MEM_SIZE];
	unsigned int	live_pl[MAX_PLAYERS];
	int				opt[OPT_MAX];
	int				cycle_curr;
	int				cycle_to_dump;
	int				cycle_to_die;
	int				cycle_tot;
	uint32_t		last_live;
	unsigned int	curr_lives;
	unsigned int	nb_pl;
}					t_env;

/*
** =============================================================================
** 						PROTOTYPES
** =============================================================================
*/

/*
** UTILS
*/

unsigned int	after_space(char *arg, unsigned int i);
unsigned int	after_word(char *arg, unsigned int i);
unsigned int	get_name_len(char *name);
char			hex_tab(uint8_t quartet);
char			*merge_args(int ac, char **av);
int				rev_bits(int num);

/*
** OPTIONS UTILS
*/

int				get_dump(char *arg, unsigned int *j);

/*
** OPTIONS
*/

void			dump(t_env *env);

/*
** UTILS AND PARSING
*/

int				error(char *error_msg, char *err_msg, char *junk);
void			free_env(t_env *env, char *arg);
int				get_data(t_env *env, char *arg);
int				get_id(t_env *env, char *arg, unsigned int *j, bool end);
int				loader(t_env *env, char *arg, unsigned int *j);
int				read_big_endian(t_env *env, int fd, bool magic);

/*
** FUNCTIONS OF THE COREWAR LOOP
*/

int				add_instruction(t_env *env, t_process *process);
void			check_live(t_env *env);
void			create_instruct(t_env *env, t_process *process);
int				create_pro(t_env *env, unsigned int i, unsigned int offset);
int				cw_loop(t_env *env);
int32_t			get_arg_value(t_env *v, t_process *p, int i, bool mod);
int32_t			get_mem_cell(t_env *v, t_process *p, size_t siz);
void			launch_instruct(t_env *env, t_process *process);
void			load_args(t_env *env, t_process *p, bool enco, bool dir);
void			write_mem_cell(t_env *v, t_process *p, int32_t value);

/*
** LISTS
*/

t_process		*new_lst(uint32_t id, uint32_t pc);
t_process		*push_lst(t_env *env, uint32_t id, uint32_t pc);
t_process		*pop_lst(t_process *process, t_process *prev);

/*
** TESTS AND DISPLAY OF THE STRUCTURES
*/

void			aff_env(t_env *env, bool all);
void			aff_player(t_player *player);
void			aff_process(t_process *process, bool all);
/*void			test_convert_instruction(void);
void			test_cw_loop(void);
void			test_get_opt_champ_loader(char *arg);
void			test_loader(void);
void			test_lst(void);
void			test_system(void);
*/

/*
** OP_FUNCTIONS
*/

void			live(t_env *env, t_process *process);
void			ld(t_env *env, t_process *process);
void			st(t_env *env, t_process *process);
void			add(t_env *env, t_process *process);
void			sub(t_env *env, t_process *process);
void			and(t_env *env, t_process *process);
void			xor(t_env *env, t_process *process);
void			or(t_env *env, t_process *process);
void			zjmp(t_env *env, t_process *process);
void			ldi(t_env *env, t_process *process);
void			sti(t_env *env, t_process *process);
void			op_fork(t_env *env, t_process *process);
void			lld(t_env *env, t_process *process);
void			lldi(t_env *env, t_process *process);
void			lfork(t_env *env, t_process *process);
void			aff(t_env *env, t_process *process);

/*
** =============================================================================
** 						FUNCTION_TABLE
** =============================================================================
*/

typedef struct s_op		t_op;

struct					s_op
{
	char				*name;
	unsigned char		nb_arg;
	unsigned char		args[3];
	unsigned int		op_code;
	uint64_t			wait_cycles;
	char				*description;
	unsigned int		encoding;
	unsigned int		direct;
	void				(*f)(t_env *env, t_process *p);
};

static const t_op			func_tab[NB_FUNC] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &aff},
};

#endif
