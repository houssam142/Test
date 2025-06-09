#include "minishell.h"

void	ft_lstadd_back(t_cmd_exec **lst, t_cmd_exec *new)
{
	t_cmd_exec	*tmp;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
	}
}
