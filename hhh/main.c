/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/22 22:55:56 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start(int ac, char **av, char **env, t_cmd_exec **env_lst)
{
	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd("Error\nmore than one argument\n", 2);
		return (1);
	}
	env_to_lst(env, env_lst);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_cmd_exec	*env_lst;
	t_token		*tok;

	if (start(ac, av, env, &env_lst) == 1)
		return (0);
	while (1)
	{
		cmd = readline("<minishell> ");
		if (!cmd)
		{
			ft_putstr_fd("exit\n" ,1);
			exit(0);
		}
		if (ft_strncmp(cmd, "", ft_strlen(cmd)) != 0)
			add_history(cmd);
		parsing_line(cmd, &tok, &env_lst);
		free(cmd);
	}
	return (0);
}
