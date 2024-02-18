/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:32:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/18 18:24:28 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SIGINT - CTRL C
	SIGQUIT - CTRL BACKSLSH
	SIGTST - CTRL Z
	CTRL D - EOF */

void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	heredoc_sig(int sig)
{
	(void)sig;
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
	struct sigaction	sig_ign;

	sig.sa_handler = new_prompt;
	sig_ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig_ign, NULL);
}

void	non_interactive_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = non_interactive_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
