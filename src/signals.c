/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:32:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/15 18:56:02 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SIGINT - CTRL C
	SIGQUIT - CTRL BACKSLSH
	SIGTST - CTRL Z
	CTRL D - EOF */

void	interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", STDERR_FILENO);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		SIG_IGN;
}
void	non_interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit (core dumped)");
		write(1, "\n", 2);
		rl_on_new_line();
	}
}

void	interactive_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = interactive_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	non_interactive_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = non_interactive_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

/* void	heredoc_h(int sig)
{
	minishell();
	(void)sig;
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_h);
	signal(SIGQUIT, SIG_IGN);
} */
