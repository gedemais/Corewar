/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:15:28 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 15:51:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Token's linked list boilerplate
*/

int		token_del_node(t_token *node)
{
	free(node);
	node = NULL;
	return (0);
}

int		token_free_lst(t_token *lst)
{
	if (lst->next)
		token_free_lst(lst->next);
	free(lst);
	return (0);
}

int			token_pushfront(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return (-1);
	if ((*lst) == NULL)
	{
		(*lst) = new;
		new->next = NULL;
		return (0);
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (0);
}

t_token		*token_lstnew(char *stream, t_tokenizer *tok)
{
	t_token	*new;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->ptr = &stream[tok->i];
	new->line = tok->line;
	new->col = tok->col;
	new->type = tok->ret;
	return (new);
}
