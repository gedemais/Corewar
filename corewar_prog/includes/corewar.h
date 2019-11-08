/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/11/08 04:10:42 by unknown          ###   ########.fr       */
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
** ==============================================================================
** 						OPTIONS
** ==============================================================================
*/

typedef enum		e_option
{
	DMP,
	D
}					t_option;

/*
** ==============================================================================
** 						OP_CODES
** ==============================================================================
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
** ==============================================================================
** 						ARGUMENTS
** ==============================================================================
*/

typedef enum		e_op_arg_type
{
	ARG_NONE,
	ARG_REG,
	ARG_DIR,
	ARG_IND,
	ARG_MX
}					t_op_arg_type;

/*
** ==============================================================================
** 						REGISTRES
** ==============================================================================
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
** ==============================================================================
** 						PROCESS
** ==============================================================================
*/

typedef struct		s_op_arg
{
	t_op_arg_type	type;
	t_reg_id		id;
	u_int32_t		arg;
}					t_op_arg;

typedef struct s_instruct	t_instruct;

struct				s_instruct
{
	t_op_arg		args[MAX_ARGS_NUMBER];
	u_int32_t		op;
};

typedef struct s_process	t_process;

struct				s_process
{
	t_process		*next;
	t_instruct		instruct;
	int32_t			r[REG_NUMBER];
	int				cycle_to_exec;
	u_int16_t		pc : 12;
	u_int32_t		tpc : 12;
	bool			alive;
	bool			carry;
	char			padding[7];
};

/*
** ==============================================================================
** 						VM AND PLAYERS
** ==============================================================================
*/

typedef struct		s_player
{
	char			com[COMMENT_LENGTH + 1];
	char			champ[CHAMP_MAX_SIZE];
	char			name[PROG_NAME_LENGTH + 1];
	char			pad[2][PAD_LENGTH];
	u_int32_t		id;
	u_int32_t		magic;
	u_int32_t		size;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_player		player[MAX_PLAYERS];
	u_int8_t			arena[MEM_SIZE];
	int				opt[OPT_MAX];
	unsigned int	live_pl[MAX_PLAYERS];
	unsigned int			verbose;
	char			pad[7];
	int				cycle_to_dump;
	int				cycle_to_die;
	int				cycle_curr;
	int				cycle_tot;
	unsigned int	curr_lives;
	unsigned int	nb_pl;
	u_int32_t		last_live;
}					t_env;

/*
** ==============================================================================
** 						PROTOTYPES
** ==============================================================================
*/

/*
** UTILS
*/

unsigned int	after_space(char *arg, unsigned int i);
unsigned int	after_word(char *arg, unsigned int i);
unsigned int	get_name_len(char *name);
char			*merge_args(int ac, char **av);
int				rev_bits(int num);

/*
** OPTIONS UTILS
*/

int				get_dump(char *arg, unsigned int *j,
		unsigned int k);

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
u_int32_t		get_mem_cell(t_env *env, t_process *p, size_t siz, u_int16_t add);
void			launch_instruct(t_env *env, t_process *process);
void			load_args(t_env *env, t_process *p, bool enco, bool dir);

/*
** FUNCTIONS TO GET THE DATA OF THE OP_FUNCTIONS
*/

void			convert_instruction(t_env *env, t_process *process);
bool			direct_size(u_int32_t c);
bool			encod_byte(u_int32_t c);
int				nb_arg(u_int32_t c);
int				wait_cycle(u_int32_t c);

/*
** CHECK OF THE ARGUMENTS OF THE OP_FUNCTIONS
*/

bool			is_op_other2_valid(t_process *p);
bool			is_op_other_valid(t_process *p);
bool			is_l_ld_st_valid(t_process *p);
bool			is_lldi_valid(t_process *p);
bool			is_sti_valid(t_process *p);
bool			is_ldi_valid(t_process *p);
bool			is_xor_valid(t_process *p);
bool			is_or_valid(t_process *p);
bool			is_and_valid(t_process *p);
bool			is_op_arg_valid(t_process *p, u_int32_t op);

/*
** LISTS
*/

t_process		*new_lst(u_int32_t id, u_int16_t pc);
t_process		*push_lst(t_process *process, u_int32_t id, u_int16_t pc);
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

u_int32_t		get_direct(t_env *env, t_process *p, t_op_arg args);
int				live(t_env *env, t_process *process);
int				ld(t_env *env, t_process *process);
int				st(t_env *env, t_process *process);
int				add(t_env *env, t_process *process);
int				sub(t_env *env, t_process *process);
int				and(t_env *env, t_process *process);
int				xor(t_env *env, t_process *process);
int				or(t_env *env, t_process *process);
int				zjmp(t_env *env, t_process *process);
int				ldi(t_env *env, t_process *process);
int				sti(t_env *env, t_process *process);
int				forky(t_env *env, t_process *process);
int				lld(t_env *env, t_process *process);
int				lldi(t_env *env, t_process *process);
int				lfork(t_env *env, t_process *process);
int				aff(t_env *env, t_process *process);

#endif
