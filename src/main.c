/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/20 11:45:56 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_heredoc;

int get_user_input(t_data *data)
{
	interactive_signals();
	data->user_input = readline("minishell: ");
	if (!data->user_input)
	{
		write(1, "exit\n", 5);
		return (FAILURE);
	}
	non_interactive_signals();
	add_history(data->user_input);
	return (SUCCESS);
}

void minishell(t_data *data)
{
	while (1)
	{
		reset_data(data);
		if (!get_user_input(data))
		{
			error_and_quit(data, 10);
			break;
		}
		if (!lexer(data))
			continue ;
		if (!parser(data))
			continue;
		if (!executor(data))
			continue;
		free_data(data);
	}
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	minishell(init_data());
	return (EXIT_SUCCESS);
}
