#include "minishell.h"

static char	*line_expansion(char *line, t_cmd_exec *env_lst)
{
	t_token	*tmp;
	char	*str;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->value = line;
	tmp->type = 'w';
	tmp->quote = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp->quote)
		return (NULL);
	tmp->quote[ft_strlen(line)] = '\0';
	tmp->quote = ft_memset(tmp->quote, '0', ft_strlen(line));
	tmp->next = NULL;
	p_expansion(tmp, env_lst);
	free(tmp->quote);
	str = tmp->value;
	free(tmp);
	return (str);
}

static void	go_heredoc(t_cmd *cmd, t_cmd_exec *env_lst, int fd_doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, cmd->op_value, \
					ft_strlen(cmd->op_value) + 1))
			break ;
		if (cmd->delimiter == 'h')
			line = line_expansion(line, env_lst);
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
	}
	if (line)
		free(line);
}

static void	child_heredoc(t_cmd *cmd, t_cmd_exec **env_lst, int *heredoc)
{
	signal(SIGINT, handle_ctrl_c_heredoc);
	close(heredoc[0]);
	go_heredoc(cmd, *env_lst, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}

static int	parent_heredoc(t_cmd *cmd, int *heredoc)
{
	int	exit_stat;

	signal(SIGINT, SIG_IGN);
	wait(&exit_stat);
	close(heredoc[1]);
	if (WIFEXITED(exit_stat))
	{
		exit_stat = WEXITSTATUS(exit_stat);
		if (exit_stat == 1)
			return (-3);
		else
			cmd->std_in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	ft_signals();
	return (0);
}

int	heredoc(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (!pid)
		child_heredoc(cmd, env_lst, heredoc);
	else
		return (parent_heredoc(cmd, heredoc));
	return (0);
}
