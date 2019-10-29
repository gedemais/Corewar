/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 21:48:54 by moguy            ###   ########.fr       */
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

/*
** ==============================================================================
** 						Options
** ==============================================================================
*/

typedef enum		e_option
{
	DMP
}					t_option;

/*
** ==============================================================================
** 						Op_codes
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
** 						Arguments
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

typedef struct		s_op_arg_reg
{
	t_op_arg_type	type;
	t_reg_id		id;
}					t_op_arg_reg;

typedef struct		s_op_arg_dir
{
	t_op_arg_type	type;
	uint32_t		arg;
}					t_op_arg_dir;

typedef union		u_op_arg
{
	struct {
		t_op_arg_type	type;
	};
	t_op_arg_dir		dir;
	t_op_arg_reg		reg;
}					t_op_arg;

/*
** ==============================================================================
** 						PROCESS
** ==============================================================================
*/


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
	int				cycle_to_exec;
	uint16_t		pc : 12;
	bool			alive;
	bool			carry;
};

/*
** ==============================================================================
** 						VM
** ==============================================================================
*/

typedef struct		s_player
{
	char			com[COMMENT_LENGTH + 1];
	char			champ[CHAMP_MAX_SIZE];
	char			name[PROG_NAME_LENGTH + 1];
	char			pad[2][PAD_LENGTH];
	int32_t			id;
	uint32_t		magic;
	uint32_t		size;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_player		player[MAX_PLAYERS];
	uint8_t			arena[MEM_SIZE];
	int				opt[OPT_MAX];
	unsigned int	live_pl[MAX_PLAYERS];
	bool			verbose[VERB_MAX];
	int				cycle_to_die;
	int				cycle_curr;
	int				cycle_tot;
	unsigned int	curr_lives;
	unsigned int	nb_pl;
}					t_env;

/////////////////////PROTOTYPES/////////////////////

//Ajouter a la lib

unsigned int	after_space(char *arg, unsigned int i);
unsigned int	after_word(char *arg, unsigned int i);
unsigned int	get_name_len(char *name);
char			*merge_args(int ac, char **av);
int				rev_bits(int num);

//Option

int				get_dump(char *arg, unsigned int *j);

//Parsing et utils

int				error(char *error_msg, char *err_msg, char *junk);
void			free_env(t_env *env, char *arg);
void			find_new_id(t_env *env, unsigned int j);
int				get_data(t_env *env, char *arg);
int				get_id(t_env *env, char *arg, unsigned int *j);
int				loader(t_env *env, char *arg, unsigned int *j);
int				read_big_endian(t_env *env, int fd, bool magic);

//Corewar loop

int				add_instruction(t_env *env, t_process *process);
int				check_live(t_env *env);
int				create_instruct(t_env *env, t_process *process);
int				create_pro(t_env *env, unsigned int i, unsigned int offset);
int				cw_loop(t_env *env);
uint32_t		get_mem_cell(t_env *env, t_process *p, size_t siz, uint16_t add);
int				launch_instruct(t_env *env, t_process *process);
void			load_args(t_env *env, t_process *p, bool enco, bool dir);

//Tableau de statique

bool			carry_flag(uint32_t c);
void			convert_instruction(t_env *env, t_process *process);
bool			direct_size(uint32_t c);
bool			encod_byte(uint32_t c);
int				nb_arg(uint32_t c);
int				wait_cycle(uint32_t c);

//Checker

bool			is_op_other2_valid(t_process *p);
bool			is_op_other_valid(t_process *p);
bool			is_l_ld_st_valid(t_process *p);
bool			is_lldi_valid(t_process *p);
bool			is_sti_valid(t_process *p);
bool			is_ldi_valid(t_process *p);
bool			is_xor_valid(t_process *p);
bool			is_or_valid(t_process *p);
bool			is_and_valid(t_process *p);
bool			is_op_arg_valid(t_process *p, uint32_t op);

//Gestion des queues

t_process		*new_lst(int32_t id, uint16_t pc);
t_process		*push_lst(t_process *process, int32_t id, uint16_t pc);
t_process		*pop_lst(t_process *process, t_process *prev);

//TESTS PROTO
/*
void			aff_env(t_env *env, bool all);
void			aff_player(t_player *player);
void			aff_process(t_process *process);
void			test_convert_instruction(void);
void			test_cw_loop(void);
void			test_get_opt_champ_loader(char *arg);
void			test_loader(void);
void			test_lst(void);
void			test_system(void);
*/
//OP_FONCTION
/*
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
*/
#endif
