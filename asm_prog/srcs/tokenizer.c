/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 17:04:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	crush_tokens(t_env *env)
{
	t_token	*t;

	t = env->tokens;
	while (t)
	{
		if ((t->type == TOK_NEWLINE && t->next && t->next->type == TOK_NEWLINE)
			|| (t->type == TOK_COMMENT && t->next && t->next->type == TOK_NEWLINE))
		{
			t->prev->next = t->next;
			t->next->prev = t->prev;
			free(t);
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
			if (tok->ret == -1 && !undefined_label_err(env, tok))
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

int		tokenizer(t_env *env, t_tokenizer tok)
{
	int		ret;

	ft_memset(&tok, 0, sizeof(t_tokenizer));
	if (init_labels(env) != 0)
		return (-1);
	if (DEBUG_MODE)
		DBPRINT("Tokenizer...")
	while (env->file[tok.i])
	{
		cross_whitespaces(env->file, &tok.i);
		ret = get_token_type(env, &tok);
		if (ret == -1)
			return (-1);
		if (tok.ret == TOK_NONE && invalid_syntax_err(env, &tok) == 0)
			return (-1);
		if (token_pushfront(&env->tokens, token_lstnew(env, &tok)) != 0)
			return (-1);
		tok.index++;
	}
	env->nb_tokens = tok.index;
	print_tokens(env->tokens);
	printf("\n");
	if (crush_tokens(env) != 0)
		return (-1);
	print_tokens(env->tokens);
	if (DEBUG_MODE)
	{
		printf("%u tokens...", env->nb_tokens);
		DBPRINT("Fine !\n\n")
	}
	return (0);
}
