/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:32:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/21 12:55:14 by ubazzane         ###   ########.fr       */
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
		end_heredoc = sig;
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

	memset(&sig, 0, sizeof(struct sigaction));
	memset(&sig_ign, 0, sizeof(struct sigaction));
	sig.sa_handler = new_prompt;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&sig_ign.sa_mask);
	sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig_ign, NULL);
}

void	non_interactive_signals(void)
{
	struct sigaction	sig;

	memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = non_interactive_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	heredoc_interrupt_signal(void)
{
	struct sigaction	sig;
	struct sigaction	sig_ign;

	memset(&sig, 0, sizeof(struct sigaction));
	memset(&sig_ign, 0, sizeof(struct sigaction));
	sig.sa_handler = heredoc_sig;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&sig_ign.sa_mask);
	sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig_ign, NULL);
}
