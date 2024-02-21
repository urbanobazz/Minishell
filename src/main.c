/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piuser <piuser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/21 11:18:53 by piuser           ###   ########.fr       */
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
			break;
		if (!lexer(data))
			continue ;
		if (!parser(data))
			continue ;
		if (!executor(data))
			continue ;
		free_data(data);
		data->err_code = COMMAND_SUCCESS;
	}
	free_env(data);
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	minishell(init_data());
	return (EXIT_SUCCESS);
}
