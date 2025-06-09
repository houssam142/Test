#include "../minishell.h"

void	lstadd_back_tok(t_token **lst, t_token *node)
{
	t_token	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = node;
		else
		{
			tmp = lst_last_tok(*lst);
			tmp->next = node;
		}
	}
}
