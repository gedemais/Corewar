#include "asm.h"

void	token_free_lst(t_token *lst)
{
	if (lst->next)
		token_free_lst(lst->next);
	free(lst);
}

int	token_pushfront(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!(*lst))
	{
		(*lst) = new;
		(*lst)->prev = NULL;
		(*lst)->next = NULL;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	return (0);
}

t_token	*token_lstnew(t_env *env, t_tokenizer *tok)
{
	t_token	*new;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->type = tok->ret;
	new->ptr = &env->file[tok->i];
	new->index = tok->i;
	new->line = tok->line;
	new->col = tok->col;
	return (new);
}
