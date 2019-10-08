/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 21:07:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	trim_tokens(t_token **lst)
{
	t_token		*tmp;

	tmp = (*lst);
	while (tmp->next)
	{
		if ((tmp->type == TOK_NEWLINE && tmp->next->type == TOK_NEWLINE)
			|| (tmp->type == TOK_COMMENT && tmp->next->type == TOK_NEWLINE))
		{
			token_snap_node(lst, tmp);
			tmp = (*lst);
			continue ;
		}
		tmp = tmp->next;
	}
}

static inline void	update_tok(char *stream, t_tokenizer *tok, unsigned int tmp)
{
	if (tok->ret == TOK_NEWLINE)
	{
		tok->line++;
		tok->line_start = tmp;
	}
	tok->col = tok->i - tok->line_start;
	if (tok->ret == TOK_COMMENT)
		while (stream[tok->i] != '\n')
			tok->i++;
	tok->len = tok->i - tmp;
}

static inline void	get_token_type(char *stream, t_tokenizer *tok)
{
	static int		(*token_fts[NTOKFUNCS])(char*, unsigned int*) = {&get_monos,
						&get_strings, &get_com_name, &get_regs, &get_numbers,
						&get_word};
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	tmp = tok->i;
	while (i < NTOKFUNCS)
	{
		if ((tok->ret = token_fts[i](&stream[tok->i], &tok->i)))
		{
			update_tok(stream, tok, tmp);
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
				printf("UNKNOWN|");
			if (tmp->type == TOK_NEWLINE)
				printf("NEWLINE\n");
			if (tmp->type == TOK_COLON)
				printf("COLON(%u)|", tmp->len);
			if (tmp->type == TOK_PERCENT)
				printf("PERCENT(%u)|", tmp->len);
			if (tmp->type == TOK_STRING)
				printf("STRING(%u)|", tmp->len);
			if (tmp->type == TOK_REG)
				printf("REGISTER(%u)|", tmp->len);
			if (tmp->type == TOK_COMMENT_CMD)
				printf("COMMENT_CMD(%u)|", tmp->len);
			if (tmp->type == TOK_NAME)
				printf("NAME_CMD(%u)|", tmp->len);
			if (tmp->type == TOK_SEPARATOR)
				printf("SEPARATOR|");
			if (tmp->type == TOK_COMMENT)
				printf("COMMENT|");
			if (tmp->type == TOK_WORD)
				printf("WORD(%u)|", tmp->len);
			if (tmp->type == TOK_NUMBER)
				printf("NUMBER(%u)|", tmp->len);
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
	int			nb_tokens = 0;

	ft_memset(&tok, 0, sizeof(t_tokenizer));
	while (env->file[tok.i])
	{
		cross_whitespaces(env->file, &tok.i);
		get_token_type(env->file, &tok);
		if (tok.ret == 0 && unex_token_err(&env->file[tok.i], tok.line, tok.col))
			return (-1);
		if (token_pushfront(&env->tokens, token_lstnew(env->file, &tok)) != 0)
			return (-1);
		nb_tokens++;
	}
	trim_tokens(&env->tokens);
	if (DEBUG_MODE)
		print_lst(env->tokens);
	return (0);
}
