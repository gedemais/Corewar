/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:13:13 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 17:28:48 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	find_label(t_label *lst, char *name, unsigned int len)
{
	t_label	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->len == len && ft_strncmp(name, tmp->ptr, len) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int		label_snap_node(t_label **lst, t_label *node)
{
	t_label	*tmp;
	t_label	*tmp2;

	tmp = (*lst);
	tmp2 = tmp->next;
	if ((*lst) == node)
	{
		free(*lst);
		(*lst) = tmp->next;
	}
	while (tmp2)
	{
		if (tmp2 == node)
		{
			tmp2 = tmp2->next ? tmp2->next : NULL;
			free(tmp->next);
			tmp->next = tmp2;
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	return (0);
}

int		label_free_lst(t_label *lst)
{
	if (lst->next)
		label_free_lst(lst->next);
	free(lst);
	return (0);
}

int			label_pushfront(t_label **lst, t_label *new)
{
	t_label	*tmp;

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

t_label		*label_lstnew(char *stream, t_token *word)
{
	t_label	*new;

	if (!(new = (t_label*)malloc(sizeof(t_label))))
		return (NULL);
	new->ptr = word->ptr;
	new->stick = (unsigned int)(word->ptr - stream);
	new->len = word->len + 1;
	return (new);
}
