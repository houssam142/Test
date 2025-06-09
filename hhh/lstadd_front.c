#include "minishell.h"

void	ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
