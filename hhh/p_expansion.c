#include "minishell.h"

static int	ft_replace(t_token *toks, int i, int j, t_cmd_exec *env_lst)
{
	char	*value;
	char	*blank;
	char	*str;

	value = ft_strdup(env_lst->value);
	toks->value[i] = '\0';
	str = ft_strjoin(toks->value, value);
	free(value);
	value = ft_strjoin(str, toks->value + j);
	free(str);
	free(toks->value);
	toks->value = value;
	blank = malloc(sizeof(char) * (ft_strlen(env_lst->value) + 1));
	if (!blank)
		return (-1);
	blank[ft_strlen(env_lst->value)] = '\0';
	ft_memset(blank, '2', ft_strlen(env_lst->value));
	toks->quote[i] = '\0';
	str = ft_strjoin(toks->quote, blank);
	free(blank);
	blank = ft_strjoin(str, toks->quote + j);
	free(str);
	free(toks->quote);
	toks->quote = blank;
	return (0);
}

static int	ft_is_found2(t_token *toks, int *i, int j, t_cmd_exec *tmp)
{
	if ((j - *i) == 1 && (tmp->name[0] == '1' || \
				(toks->value[j] != '\"' && toks->value[j] != '\'')))
		tmp->value = malloc(sizeof(char) * 2);
	else
		tmp->value = malloc(sizeof(char) * 1);
	if (!tmp->value)
		return (-1);
	if ((j - *i) == 1 && (tmp->name[0] == 1 || \
			     (toks->value[j] != '\"' && toks->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';
	tmp->next = NULL;
	return (1);
}

static int	ft_is_found(t_token *toks, int *i, int j, int quote)
{
	t_cmd_exec	*tmp;
	int		res;

	tmp = malloc(sizeof(t_cmd_exec) * 1);
	if (!tmp)
		return (-1);
	tmp->name = malloc(sizeof(char) * 2);
	if (!tmp->name)
		return (-1);
	if (quote == 1)
		tmp->name[0] = '1';
	else
		tmp->name[1] = '0';
	tmp->name[1] = '\0';
	ft_is_found2(toks, i, j, tmp);
	res = ft_replace(toks, *i, j, tmp);
	if (!((j - *i) == 1 && (tmp->name[0] == '1' || \
			      (toks->value[j] == '\"' || toks->value[j] == '\''))))
		*i = *i - 1;
	lst_del(tmp, &free);
	return (res);	
}

static int	search_and_replace(t_token *t, int *i, t_cmd_exec *env_lst, int w)
{
	char	*new_str;
	int	j;

	j = *i + 1;
	while (t->value[j] != ' ' && t->value[j] && t->value[j] != '\t' && \
			t->value[j] != '\"' && t->value[j] != '\'' && t->value[j] != '/' \
			&& t->value[j] != '$' && t->value[j] != '=')
		j++;
	new_str = ft_substr(t->value, *i + 1, j - *i - 1);
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, new_str, ft_strlen(new_str) + 1))
			break ;
		env_lst = env_lst->next;
	}
	if (!new_str[0])
	{
		free(new_str);
		return (0);
	}
	free(new_str);
	if (env_lst != NULL)
		return (ft_replace(t, *i, j, env_lst));
	else
		return (ft_is_found(t, i, j, w));
}

void	p_expansion(t_token *toks, t_cmd_exec *env_lst)
{
	int	i;

	i = -1;
	while (toks->value[++i])
	{
		if (toks->value[i] == '\'')
		{
			i++;
			while (toks->value[i] != '\'' && toks->value[i])
				i++;
		}
		else if (toks->value[i] == '\"')
		{
			while (toks->value[++i] != '\"')
				if (toks->value[i] == '$')
					search_and_replace(toks, &i, env_lst, 1);
		}
		else if (toks->value[i] == '$')
			search_and_replace(toks, &i, env_lst, 0);
	}
}
