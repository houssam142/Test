#include "../minishell.h"

void	lst_del(t_cmd_exec *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->name);
		del(lst->value);
		free(lst);
	}
}

void	lst_del_tok(t_token *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->value);
		del(lst->quote);
		free(lst);
	}
}
