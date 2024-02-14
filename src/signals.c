/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:32:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/14 17:44:38 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SIGINT - CTRL C
	SIGQUIT - CTRL BACKSLSH
	SIGTST - CTRL Z
	CTRL D - ??? */

void	new_prompt(void)
{
	ft_printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}
void	signal_handler(int sig)
{
	if (sig == SIGINT)
		minishell();
	else if (sig == SIGQUIT)
		SIG_IGN;
}
void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		unlink(".heredoc");
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGQUIT)
	{
		unlink(".heredoc");
		exit(EXIT_SUCCESS);
	}
}

void	init_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = signal_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
void	init_heredoc_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
