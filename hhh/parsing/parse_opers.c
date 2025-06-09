#include "../minishell.h"

static int	parsing_in(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	fd;

	if (ft_strncmp(cmd->op, "<", 2) == 0)
	{
		fd = open(cmd->op_value, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (cmd->std_in != 0)
			close(cmd->std_in);
		cmd->std_in = fd;
	}
	else if (!ft_strncmp(cmd->op, "<<", 3))
		return (heredoc(cmd, env_lst));
	return (0);
}	

static void	parsing_out(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->op_value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->std_out != 1)
		close(cmd->std_out);
	cmd->std_out = fd;
}

static int	parsing_redirs(t_token **toks, t_cmd *cmd, \
		t_token **tmp, t_cmd_exec **env_lst)
{
	int	fd;

	if (cmd->op_value)
		free(cmd->op_value);
	cmd->op_value = ft_strdup((*toks)->value);
	cmd->delimiter = (*toks)->type;
	*tmp = *toks;
	*toks = (*toks)->next;
	lst_del_tok(*tmp, &free);
	if (!ft_strncmp(cmd->op, ">", 2))
	{
		fd = open(cmd->op_value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->std_out != 1)
			close(cmd->std_out);
		cmd->std_out = fd;
	}
	else if (ft_strncmp(cmd->op, ">>", 3) == 0)
		parsing_out(cmd);
	else
		return (parsing_in(cmd, env_lst));
	return (0);
}

int	parsing_opers(t_token **toks, t_cmd *cmd, t_cmd_exec **env_lst)
{
	t_token	*tmp;
	int	stat;

	stat = 0;
	while ((*toks) != NULL && (*toks)->type != 'c' && stat >= 0)
	{
		if (cmd->op != NULL)
			free(cmd->op);
		cmd->op = ft_strdup((*toks)->value);
		tmp = *toks;
		*toks = (*toks)->next;
		lst_del_tok(tmp, &free);
		if (*toks && ((*toks)->type == 'v' || \
					(*toks)->type == 'h' || (*toks)->type == 'H'))
			stat = parsing_redirs(toks, cmd, &tmp, env_lst);
		else
		{
			ft_putstr_fd("Minishell Syntax error: Undefined value after " \
					"operator\n", 2);
			return (-2);
		}
	}
	return (stat);
}
