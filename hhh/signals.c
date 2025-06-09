#include "minishell.h"

static void	suppress_out(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p))
		perror("Minishell: tcsetattr");
}

static void	ft_sigint_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ft_handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	handle_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	ft_signals(void)
{
	suppress_out();
	signal(SIGINT, ft_sigint_ctrl_c);
	signal(SIGQUIT, ft_handle_sigquit);
}
