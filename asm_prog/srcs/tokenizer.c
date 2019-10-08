/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 17:22:42 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	update_tok(t_tokenizer *tok)
{
	if (tok->ret == TOK_NEWLINE)
	{
		tok->line++;
		tok->col = 0;
	}
	tok->col += tok->i;
}

static inline int	unex_token_err(char *line, unsigned int nline)
{
	char		*nb_line;
	unsigned int	i;

	i = 0;
	if (!(nb_line = ft_itoa((int)nline)))
		return (1);
	ft_putstr_fd("Unexpected token at line ", 2);
	ft_putstr_fd(nb_line, 2);
	free(nb_line);
	ft_putendl_fd(":", 2);
	while (line[i] && line[i] != '\n')
	{
		ft_putchar_fd(line[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

static inline void	get_token_type(char *stream, t_tokenizer *tok)
{
	static int		(*token_fts[NTOKFUNCS])(char*, unsigned int*) = {&get_monos,
						&get_strings, &get_ops, &get_regs, &get_com_name};
	unsigned int	i;

	i = 0;
	while (i < NTOKFUNCS)
	{
		if ((tok->ret = token_fts[i](&stream[tok->i], &tok->i)))
		{
			update_tok(tok);
			break ;
		}
		i++;
	}
}

static inline void	print_lst(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
			if (tmp->type == TOK_NONE)
				printf("Unknown->");
			if (tmp->type == TOK_NEWLINE)
				printf("Newline\n");
			if (tmp->type == TOK_COLON)
				printf("Colon->");
			if (tmp->type == TOK_PERCENT)
				printf("Percent->");
			if (tmp->type == TOK_OP)
				printf("OP->");
			if (tmp->type == TOK_KEY)
				printf("Key->");
			if (tmp->type == TOK_LABEL)
				printf("Label->");
			if (tmp->type == TOK_STRING)
				printf("String->");
			if (tmp->type == TOK_REG)
				printf("Register->");
			if (tmp->type == TOK_COMMENT)
				printf("Comment->");
			if (tmp->type == TOK_NAME)
				printf("Name->");
		tmp = tmp->next;
	}
	printf("\n");
	fflush(stdout);
}

static inline void	cross_whitespaces(char *stream, unsigned int *i)
{
	char	c;

	while (stream[*i])
	{
		c = stream[*i];
		if (c == '\n' || !ft_is_whitespace(c))
			break ;
		*i += 1;
	}
}

int		tokenizer(t_env *env)
{
	t_tokenizer	tok;

	ft_memset(&tok, 0, sizeof(t_tokenizer));
	while (env->file[tok.i])
	{
		cross_whitespaces(env->file, &tok.i);
		get_token_type(env->file, &tok);
		if (tok.ret == 0 && unex_token_err(&env->file[tok.i], tok.line))
		{
			print_lst(env->tokens);
			return (-1);
		}
		if (token_pushfront(&env->tokens, token_lstnew(env->file, &tok)) != 0)
			return (-1);
	}
	print_lst(env->tokens);
	return (0);
}
