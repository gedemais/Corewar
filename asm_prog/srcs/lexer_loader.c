/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:15:53 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 17:37:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		load_lex_name_prop(t_env *env, t_lexem *lex, t_token **tok)
{
	char	*err;
	int		ret;

	ret = 2;
	printf("load_lex_name_prop\n");
	if (!(*tok) || (*tok)->type != TOK_P_NAME)
		return (0);
	*tok = (*tok)->next;
	if (!(lex->args[0].str = ft_strndup((*tok)->ptr, (int)(*tok)->len)))
		return (-1);
	if (ft_strlen(lex->args[0].str) >= PROG_NAME_LENGTH)
	{
		if (!(err = ft_itoa(PROG_NAME_LENGTH)))
			return (-1);
		ft_putstr_fd(NAME_LENGTH_ERR, 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd(" bytes.", 2);
		return (-1);
	}
	lex->type = LEX_NAME_PROP;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	return (ret);
}

int		load_lex_comment_prop(t_env *env, t_lexem *lex, t_token **tok)
{
	char	*err;
	int		ret;

	ret = 2;
	printf("load_lex_comment_prop\n");
	if (!(*tok) || (*tok)->type != TOK_P_COM)
		return (0);
	*tok = (*tok)->next;
	if (!(lex->args[0].str = ft_strndup((*tok)->ptr, (int)(*tok)->len)))
		return (-1);
	if (ft_strlen(lex->args[0].str) >= PROG_NAME_LENGTH)
	{
		if (!(err = ft_itoa(COMMENT_LENGTH)))
			return (-1);
		ft_putstr_fd(COMMENT_LENGTH_ERR, 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd(" bytes.", 2);
		return (-1);
	}
	lex->type = LEX_COMMENT_PROP;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	return (ret);
}

int		load_lex_label(t_env *env, t_lexem *lex, t_token **tok)
{
	printf("load_lex_label_prop\n");
	if (!(*tok) || (*tok)->type != TOK_LABEL)
		return (0);
	lex->type = LEX_LABEL;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	lex->args[0].str = NULL;
	return ((*tok)->next->type == TOK_NEWLINE ? 2 : 1);
}

int		load_lex_opcode(t_env *env, t_lexem *lex, t_token **tok)
{
	printf("load_lex_opcode_prop\n");
	if (!(*tok) || (*tok)->type != TOK_OPCODE)
		return (0);
	(void)env;
	(void)lex;
	(void)tok;
	return (0);
}
