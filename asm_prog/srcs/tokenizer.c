/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/16 11:55:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	crush_tokens(t_env *env)
{
	t_token	*t;
	int		tmp;

	t = env->tokens;
	while (t)
	{
		if (t->type == TOK_DLABA || t->type == TOK_INDLABA)
		{
			if ((tmp = find_label_index(env->labels, t, env->nb_labels)) == -1)
				return (-1);
			t->label = (unsigned int)tmp;
			t->type = (t->type == TOK_DLABA) ? TOK_LNUMBER : TOK_NUMBER;
		}
		if ((t->type == TOK_NEWLINE && t->next && t->next->type == TOK_NEWLINE)
			|| t->type == TOK_COMMENT || (t == env->tokens && t->type == TOK_NEWLINE))
		{
			token_snap_node(&env->tokens, t);
			env->nb_tokens--;
			t = env->tokens;
			continue ;
		}
		t = t->next;
	}
	return (0);
}

static inline void	update_tok(char *stream, t_tokenizer *tok, unsigned int tmp)
{
	if (tok->ret == TOK_NEWLINE)
	{
		tok->line++;
		tok->line_start = tmp + 1;
	}
	tok->col = tok->i - tok->line_start;
	if (tok->ret == TOK_COMMENT)
		while (stream[tok->i] != '\n')
			tok->i++;
	tok->len = tok->i - tmp;
}

static inline int	get_token_type(t_env *env, t_tokenizer *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	tmp = tok->i;
	while (i < NB_TOKENS_FUNCS)
	{
		if ((tok->ret = g_token_fts[i](env, &env->file[tok->i], &tok->i)))
		{
			if (tok->ret == -1)
				return (-1);
			update_tok(env->file, tok, tmp);
			break ;
		}
		update_tok(env->file, tok, tmp);
		i++;
	}
	return (0);
}

void	cross_whitespaces(char *stream, unsigned int *i)
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
/*
static inline void	print_token(int tok)
{
	switch (tok)
	{
	case 1:
		printf("name_properity->");
		break;
	case 2:
		printf("comment_properity->");
		break;
	case 3:
		printf("string->");
		break;
	case 4:
		printf("register->");
		break;
	case 5:
		printf("label->");
		break;
	case 6:
		printf("number->");
		break;
	case 7:
		printf("lnumber->");
		break;
	case 8:
		printf("direct label access->");
		break;
	case 9:
		printf("indirect label access->");
		break;
	case 10:
		printf("Opcode->");
		break;
	case 11:
		printf("Separator->");
		break;
	case 12:
		printf("newline\n");
		break;
	case 13:
		printf("comment->");
		break;
	default:
		printf("NONE->");
		break;
	}
	fflush(stdout);
}

static inline void	print_tokens(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_token(tmp->type);
		tmp = tmp->next;
	}
}
*/
int		tokenizer(t_env *env)
{
	int		ret;

	ft_memset(&env->tok, 0, sizeof(t_tokenizer));
	if (init_labels(env) != 0)
		return (-1);
	while (env->file[env->tok.i])
	{
		cross_whitespaces(env->file, &env->tok.i);
		ret = get_token_type(env, &env->tok);
		if (ret == -1)
			return (-1);
		if (env->tok.ret == TOK_NONE && invalid_syntax_err(env, &env->tok) == 0)
			return (-1);
		if (token_pushfront(&env->tokens, token_lstnew(env, &env->tok)) != 0)
			return (-1);
		env->tok.index++;
	}
	env->nb_tokens = env->tok.index;
	if (crush_tokens(env) != 0)
		return (-1);
	//print_tokens(env->tokens);
	return (0);
}
