#include "asm.h"

static inline void	print_err_name(char *err)
{
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(STOP, 2);
}

static inline void	print_cursor(char *line, unsigned int col)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	while (i < col)
	{
		if (ft_is_whitespace(line[i]))
			ft_putchar_fd(line[i], 2);
		else
			ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('^', 2);
	ft_putchar_fd('\n', 2);
}

static inline void	print_line_n_col(unsigned int line, unsigned int col, bool colon)
{
	char		*nline;
	char		*ncol;

	if (!(nline = ft_itoa((int)line + 1))
		|| !(ncol = ft_itoa((int)col)))
		return ;
	ft_putstr_fd(LINE, 2);
	ft_putstr_fd(nline, 2);
	free(nline);
	ft_putstr_fd(COL, 2);
	ft_putstr_fd(ncol, 2);
	free(ncol);
	if (colon)
		ft_putendl_fd(":", 2);
}

int					expected_newline_err(t_token *tok)
{
	char		*nline;

	if (!(nline = ft_itoa(tok->line)))
		return (-1);
	print_err_name(EX_NEWLINE);
	ft_putstr_fd(LINE, 2);
	ft_putendl_fd(nline, 2);
	free(nline);
	return (0);
}

int					property_error(char *file, t_token *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = tok->index;
	print_err_name((tok->type == TOK_P_COM) ? COMMENT_CMD_ERR : NAME_CMD_ERR);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	while (i > 0 && file[i] != '\n')
		i--;
	i++;
	tmp = i;
	while (file[i] != '\n')
	{
		ft_putchar_fd(file[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&file[tmp], tok->col);
	return (0);
}

int					undefined_label_err(t_env *env)
{
	unsigned int	i;

	i = 0;
	print_err_name(UNDEFINED_LABEL);
	print_line_n_col(env->tok.line, env->tok.col, true);
	while (&env->file[env->tok.line_start + i] && env->file[env->tok.line_start + i] != '\n')
	{
		ft_putchar_fd(env->file[env->tok.line_start + i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[env->tok.line_start], env->tok.col);
	return (0);
}

int					invalid_syntax_err(t_env *env, t_tokenizer *tok)
{
	unsigned int	j;

	j = 0;
	print_err_name(INVALID_SYNTAX);
	print_line_n_col(tok->line, tok->col, true);
	while (env->file[tok->line_start + j]
		&& env->file[tok->line_start + j] != '\n')
	{
		ft_putchar_fd(env->file[tok->line_start + j], 2);
		j++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[tok->line_start], tok->col);
	return (0);
}

static inline int	get_type_str(int id, char *buff)
{
	if (id == TOK_REG)
	{
		ft_strcpy(buff, "reg");
		return (0);
	}
	else if (id == TOK_NUMBER)
	{
		ft_strcpy(buff, "indirect_num");
		return (0);
	}
	else if (id == TOK_LNUMBER)
	{
		ft_strcpy(buff, "direct_num");
		return (0);
	}
	return (1);
}

static inline void	op_usage(int op)
{
	char			type[MAX_TYPE_SIZE];
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putchar_fd(' ', 2);
	while (i < 9)
	{
		j = 0;
		ft_putstr_fd("[", 2);
		while (j < 3 && g_op_args[op][i + j])
		{
			if (get_type_str(g_op_args[op][i + j], &type[0]) != 0)
				return ;
			ft_putstr_fd(&type[0], 2);
			if (i + j + 1 < 9 && g_op_args[op][i + j + 1])
				ft_putstr_fd("|", 2);
			j++;
		}
		ft_putstr_fd("] ", 2);
		i += 3;
	}
}

int					invalid_op_parameter(t_token *tok, int op)
{
	char				type[MAX_TYPE_SIZE];
	unsigned int		j;

	j = 0;
	print_err_name(INVALID_OP_PARAM);
	print_line_n_col(tok->line, tok->col, true);
	ft_putstr_fd("Incompatible type ", 1);
	get_type_str(tok->type, &type[0]);
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(STOP, 2);
	ft_putstr_fd(" for ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putendl_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}

int					too_few_op_args(t_token *tok, int op)
{
	print_err_name(TOO_FEW_ARGS);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		unknown_properity(char *stream)
{
	unsigned int	i;

	i = 0;
	print_err_name(UNKNOWN_PROPERITY);
	ft_putstr_fd(": ", 2);
	while (stream[i] && stream[i] != '\n')
		i++;
	write(2, stream, i);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		not_eno_args(t_token *tok, int op)
{
	unsigned int	i;

	i = 0;
	print_err_name(NOT_ENO_ARGS);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}

int		invalid_label_err(t_token *tok)
{
	unsigned int	i;

	i = 0;
	print_err_name(INVALID_LABEL);
	print_line_n_col(tok->line, tok->col, true);
	while (tok->ptr[i] && tok->ptr[i] != '\n')
	{
		ft_putchar_fd(tok->ptr[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

int		dup_label_err(char *label, unsigned int i, unsigned int first)
{
	unsigned int	j;

	j = 0;
	print_err_name(DUP_LABEL);
	ft_putchar_fd('\n', 2);
	while (label[first] && label[first] != '\n')
	{
		ft_putchar_fd(label[first], 2);
		first++;
	}
	ft_putchar_fd('\n', 2);
	while (label[i] && label[i] != '\n')
	{
		ft_putchar_fd(label[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

int		missing_properity(bool name, bool comment)
{
	if (name)
		ft_putstr_fd("name ", 2);
	if (name && comment)
	{
		ft_putstr_fd(STOP, 2);
		ft_putstr_fd("and", 2);
	}
	if (comment)
		ft_putstr_fd(" comment ", 2);
	ft_putstr_fd(L_RED, 2);
	ft_putendl_fd(MISSING_PROPERITY, 2);
	ft_putstr_fd(STOP, 2);
	return (1);
}

int		dup_properity_err(char *file, unsigned int i)
{
	print_err_name(DUP_PROPERITY);
	while (file[i] && file[i] != '\n')
	{
		ft_putchar_fd(file[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

bool	check_after(t_token *tok)
{
	while (tok)
	{
		if (tok->type != TOK_NEWLINE)
			return (false);
		tok = tok->next;
	}
	return (true);
}

int		unex_token(t_token *tok)
{
	ft_putstr_fd(L_RED, 2);
	print_err_name(UNEX_TOKEN);
	ft_putstr_fd(STOP, 2);
	print_line_n_col(tok->line, tok->col, fglse);
gft_putchar_fd('\n', 2);
	return (0);
}
