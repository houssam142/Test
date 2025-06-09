#include "../minishell.h"

static void	cmd_free(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd != NULL)
	{
		if (cmd->args)
		{
			while (cmd->args[++i] != NULL)
				free(cmd->args[i]);
			free(cmd->args);
		}
		if (cmd->path)
			free(cmd->path);
		if (cmd->op)
			free(cmd->op);
		if (cmd->op_value)
			free(cmd->op_value);
		free(cmd);
	}
}

static int	opers(t_token *toks)
{
	while (toks)
	{
		if (toks->type == 'o')
		{
			if (ft_strncmp(toks->value, ">", 2) == 0 || \
					ft_strncmp(toks->value, ">>", 3) == 0 || \
					ft_strncmp(toks->value, "<", 2) == 0 || \
					ft_strncmp(toks->value, "<<", 3) == 0)
				toks->type = 'r';
			else if (ft_strncmp(toks->value, "|", 2) == 0)
				toks->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(toks->value, 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		toks = toks->next;
	}
	return (0);
}

static void	clear_all(t_cmd **cmds, t_token **tokens)
{
	lst_clear_tok(tokens, &free);
	while (*cmds != NULL)
	{
		cmd_free(*cmds);
		*cmds = (*cmds)->next;
	}
}

int	parsing_line(char *line, t_token **toks, t_cmd_exec **env_lst)
{
	int	count;
	char	chars[11];
	t_cmd	*cmd;

	cmd = NULL;
	*toks = NULL;
	ft_strlcpy(chars, "<>|&;() \t\n", 11);
	count = tokens_count(line, chars);
	if (count > 0)
	{
		toks_arr(line, chars, toks);
		if (opers(*toks) == -1)	
		{
			lst_clear_tok(toks, &free);
			return (-1);
		}
		toks_to_struct(toks, &cmd, env_lst);
		clear_all(&cmd, toks);
	}
	return (1);
}

