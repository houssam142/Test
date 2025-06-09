#include "../minishell.h"

static void	helper(t_token *toks, int *i, char c)
{
	toks->quote[*i] = '1';
	while (toks->value[++(*i)] != c)
		toks->quote[*i] = '0';
	toks->quote[*i] = '1';
}

void	quote_count(t_token *toks)
{
	int	i;

	i = -1;
	if (toks != NULL)
	{
		while (toks->value[++i])
		{
			if (toks->value[i] == '\'')
				helper(toks, &i, '\'');
			else if (toks->value[i] == '\"')
				helper(toks, &i, '\"');
			else
				toks->quote[i] = '0';
		}
	}
}
