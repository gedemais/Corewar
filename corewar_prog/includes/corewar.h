/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:10 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:24:07 by moguy            ###   ########.fr       */
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
	int			direct4;
	short		direct2;
	short		indirect;
	char		registre;
};

typedef struct s_instruct	t_instruct;

struct			s_instruct
{
	t_type		arg[MAX_ARG_FUNC];
	char		type[MAX_ARG_FUNC];
	char		padding;
	int			wait_cycle;
	char		op_code;
	char		pad[3];
};

typedef struct s_process	t_process;

struct			s_process
{
	t_process	*next;
	t_instruct	instruct;
	int			r[REG_NUMBER];
	int			carry;
	int			player;
	uint16_t	pad : 4;
	uint16_t	pc : 12;
	uint16_t	pad2 : 4;
	uint16_t	pci : 12;
	int			padding;
};

typedef struct		s_player
{
	char			comment[COMMENT_LENGTH + 1];
	char			champ[CHAMP_MAX_SIZE];
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			pad2[4];
	long long int	id;
	uint32_t		pad;
	uint32_t		magic;
	uint32_t		siz;
	uint16_t		first_pc : 12;
	uint16_t		pad_bits : 4;
	bool			dead;
	char			pad_bytes;
}					t_player;

typedef struct		s_env
{
	t_process		*process;
	t_player		player[MAX_PLAYERS];
	unsigned int	nb_lives[MAX_PLAYERS];
	char			arena[MEM_SIZE];
	long long int	dump;
	int				cycle;
	int				curr_cycle;
	int				cycle_to_die;
	unsigned int	live_tot;
	unsigned int	nb_players;
	int				pad;
}					t_env;

/////////////////////PROTOTYPES/////////////////////

//Ajouter a la lib

unsigned int	after_space(char *arg, unsigned int i);
unsigned int	after_word(char *arg, unsigned int i);
unsigned int	get_name_len(char *name);
short			hex_conv2(char a, char b);
int				hex_conv4(char a, char b, char c, char d);
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

int				add_instruction(t_env *env, t_process *process);
int				check_op(t_env *env, t_process *process);
void			check_type(t_env *e, t_process *process);
int				create_first_process(t_env *env);
int				cw_loop(t_env *env);
int				load_op(t_env *env, t_process *process);

//Tableau de statique

bool			carry_flag(char c);
void			convert_instruction(t_env *env, t_process *process);
bool			direct_size(char c);
bool			encoding_byte(char c);
int				nb_arg(char c);
int				wait_cycle(char c);
int				check_dying_process(t_env *env);

//Gestion des queues

t_process		*new_lst(long long int id, uint16_t pc);
t_process		*push_lst(t_process *process, long long int id, uint16_t pc);
t_process		*pop_lst(t_process *process, t_process *tmp);

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

int				live(t_env *env, t_process *process);
int				ld(t_env *env, t_process *process);
/*int				st(t_env *env, t_process *process);
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
