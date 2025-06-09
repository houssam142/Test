#include "../minishell.h"

void	lst_clear(t_cmd_exec **lst, void (*del)(void *))
{
	t_cmd_exec	*tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			lst_del(*lst, del);
			*lst = tmp;
		}
	}
}

void	lst_clear_tok(t_token **lst, void (del)(void *))
{
	t_token	*tmp;

	if (lst && *lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			lst_del_tok(*lst, del);
			*lst = tmp;
		}
	}
}
