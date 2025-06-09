#include "minishell.h"

void	change_stat(t_cmd_exec **env_lst, int stat)
{
	t_cmd_exec	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	tmp->status = stat;
	if (tmp->value)
		free(tmp->value);	
	tmp->value = ft_itoa(tmp->status);
}
