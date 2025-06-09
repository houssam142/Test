#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <errno.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>


typedef struct s_token
{
	char		type;
	char		*quote;
	char		*value;
	struct s_token	*next;
} t_token;

typedef struct s_cmd_exec
{
	char			*name;
	char			meaning;
	char			*value;
	int			status;
	int			sigint_child;
	t_token			*token;
	struct termios		origin_term;
	struct	s_cmd_exec	*next;
}	t_cmd_exec;

typedef struct s_cmd
{
	int		id;
	int		builtin;
	char		**args;
	char		*op;
	char		*op_value;
	int		std_in;
	int		std_in_dup1;
	int		std_out_dup1;
	int		std_out;
	int		std_err;
	int		pipe_in;
	int		path_error;
	int		pipe_out;
	int		pipe;
	char		*path;
	char		delimiter;
	struct s_cmd	*next;
}t_cmd;

int		env_to_lst(char **env, t_cmd_exec **env_lst);
void		toks_arr(char *line, char *chars, t_token **toks);
void		change_stat(t_cmd_exec **env_lst, int stat);
int		parsing_line(char *line, t_token **toks, t_cmd_exec **env_lst);
void		lst_clear(t_cmd_exec **lst, void (*del)(void *));
void		p_expansion(t_token *toks, t_cmd_exec *env_lst);
void		ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new);
void		ft_lstadd_back(t_cmd_exec **lst, t_cmd_exec *new);
int		arg_count(t_token **toks, t_cmd *cmd);
void		lst_del(t_cmd_exec *lst, void (*del)(void *));
int		heredoc(t_cmd *cmd, t_cmd_exec **env_lst);
void		handle_ctrl_c_heredoc(int sig);
void		word_split(t_token **toks, t_cmd_exec *env_lst);
void		lst_del_tok(t_token *lst, void (*del)(void *));
void		ft_lstclear(t_cmd_exec **lst, void (*del)(void *));
t_token		*lst_new_ele_tok(char type, char *value);
t_cmd_exec	*lst_new_ele(char *name, char *value);
void		toks_trim(t_token **toks);
t_token		*lst_last_tok(t_token *lst);
void		lstadd_back_tok(t_token **lst, t_token *node);
int		change_dir(char *path, t_cmd_exec **env_lst);
int		cd(t_cmd *cmd, t_cmd_exec **env_lst);
int		tokens_count(char *line, char *chars);
int		pwd(t_cmd_exec **env_lst);
int		unset(t_cmd *cmd, t_cmd_exec **env_lst);
int		echo(t_cmd *cmd, t_cmd_exec **env_lst);
int		env(t_cmd_exec **env_lst);
int		ft_exit(t_cmd *cmd, t_cmd_exec **env_lst);
int		ft_export(t_cmd *cmd, t_cmd_exec **env_lst);
int		check_var_name(char *str, int *res, t_cmd_exec **env_lst);
void		shell_vl(t_cmd_exec **env_lst);
t_cmd_exec	*ft_lstlast(t_cmd_exec *lst);
void		lst_clear_tok(t_token **lst, void (del)(void *));
int		toks_to_struct(t_token **toks, t_cmd **cmd, t_cmd_exec **env_lst);
void		child_proc(t_cmd **cmd, t_cmd_exec **env_lst, int id);
char		*find_cmd(t_cmd *cmd, t_cmd_exec *env_lst);
void		exec_built(t_cmd *cmd, t_cmd_exec **env_lst, int child_par);
void		ft_signals(void);
void		quote_count(t_token *toks);
int		parsing_opers(t_token **toks, t_cmd *cmd, t_cmd_exec **env_lst);
void		quote_del(t_token *toks);
char		*ft_strjoin_sep(char *path, char *cmd, char c);
void		arr_free(char **arr);
void		dups(t_cmd *tmp);
char		**env_lst_to_arr(t_cmd_exec *env_lst, char meaning, int quote);
void		exec(t_cmd **cmd, t_cmd_exec **env_lst);

#endif
