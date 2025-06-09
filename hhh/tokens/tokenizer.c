#include "../minishell.h"

static void	single_quotes(char *line, int *i, int *count, char *chars)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\0')
		{
			ft_putstr_fd("Error\nfound not closed quote", 2);
			(*count) = -300;
		}
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(chars, line[*i]) != 0)
			(count)++;
	}
}

static void	double_quotes(char *line, int *i, int *count, char *chars)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] != '\"' && line[*i])
			(*i)++;
		if (line[*i] == '\0')
		{
			ft_putstr_fd("Error\nfount not closed quote\n", 2);
			(*count) = -300;
		}
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(chars, line[*i]) != 0)
			(*count)++;
	}
}

static void	words_and_opers(char *line, int *i, int *count, char *chars)
{
	if (ft_strchr(chars, line[*i]) != 0 && line[*i] != '\0')
	{
		while (ft_strchr(chars, line[*i] == 0) && line[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0')
	{
		while (ft_strchr(chars, line[*i]) == 0 && \
				line[*i] && line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			(*count)++;
	}
}

int	tokens_count(char *line, char *chars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		single_quotes(line, &i, &count, chars);
		double_quotes(line, &i, &count, chars);
		words_and_opers(line, &i, &count, chars);
	}
	return (count);
}
