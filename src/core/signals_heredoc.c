/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:11:19 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/25 13:14:33 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SIGINT - CTRL C
	SIGQUIT - CTRL BACKSLSH
	SIGTST - CTRL Z
	CTRL D - EOF */

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
		g_end_heredoc = sig;
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
