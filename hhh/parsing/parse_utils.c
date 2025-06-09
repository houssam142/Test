#include "../minishell.h"

static void	final_parsing(t_token **toks, t_cmd_exec *env_lst)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *toks;
	tmp2 = tmp;
	while (tmp && tmp->type != 'c')
	{
		if (tmp2 != tmp && tmp2->type == 'r' && \
				ft_strncmp(tmp2->value, "<<", 3) == 0)
			tmp->type = 'h';
		quote_count(tmp);
		if (tmp->type != 'h')
			p_expansion(tmp, env_lst);
		tmp2 = tmp;
		tmp = tmp->next;
	}
	word_split(toks, env_lst);
	tmp = *toks;
	while (tmp && tmp->type != 'c')
	{
		if (tmp->type != 'r')
			quote_del(tmp);
		tmp = tmp->next;
	}
}

static int	parsing_cmd(t_token **toks, t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	i;

	final_parsing(toks, *env_lst);
	arg_count(toks, cmd);
	i = parsing_opers(toks, cmd, env_lst);
	if (i == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->op_value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		change_stat(env_lst, 1);
	}
	if (i == -2)
	{
		change_stat(env_lst, 258);
		return (-1);
	}
	if (i == -3)
		change_stat(env_lst, 1);
	if (i < 0)
		return (-1);
	return (0);
}

static void	cmd_init(t_cmd **cmd)
{
	(*cmd) = (malloc(sizeof(t_cmd)));
	(*cmd)->id = 0;
	(*cmd)->args = NULL;
	(*cmd)->op = NULL;
	(*cmd)->path = NULL;
	(*cmd)->path_error = 0;
	(*cmd)->op_value = 0;
	(*cmd)->builtin = 0;
	(*cmd)->std_in = 0;
	(*cmd)->std_out = 1;
	(*cmd)->std_err = 2;
	(*cmd)->pipe = 0;
	(*cmd)->pipe_out = 0;
	(*cmd)->pipe_in = 0;
	(*cmd)->next = NULL;
}

static int	parse_pipe(t_token **toks, t_cmd *last)
{
	t_token	*tmp;
	t_cmd	*new_cmd;
	int	fd[2];

	last->pipe = 1;
	tmp = *toks;
	*toks = (*toks)->next;
	lst_del_tok(tmp, &free);
	if (pipe(fd) == -1)
		return (-1);
	cmd_init(&new_cmd);
	last->next = new_cmd;
	last->pipe_out = fd[1];
	last->next->pipe_in = fd[0];
	return (0);
}

int	toks_to_struct(t_token **toks, t_cmd **cmd, t_cmd_exec **env_lst)
{
	t_cmd	*last;
	int	id;

	id = 0;
	cmd_init(cmd);
	if (parsing_cmd(toks, *cmd, env_lst) == -1)
		return (-1);
	(*cmd)->id = id;
	while ((*toks) && ft_strncmp((*toks)->value, "|", 2) == 0)
	{
		last = *cmd;
		while (last->next != NULL)
			last = last->next;
		parse_pipe(toks, last);
		last = *cmd;
		while (last->next)
			last = last->next;
		if (parsing_cmd(toks, last, env_lst) == -1)
			return (-1);
		last->id = ++id;
	}
	return (0);
}
