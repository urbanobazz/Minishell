/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:18:42 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 20:12:29 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	get_user_input(t_data *data)
{
	interactive_signals();
	data->user_input = readline("minishell: ");
	if ((data->user_input && ft_strcmp(data->user_input, "exit") == 0)
		|| !data->user_input)
	{
		write(1, "Exit\n", 5);
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	non_interactive_signals();
	add_history(data->user_input);
}

void	minishell(t_data *data)
{
	reset_data(data);
	get_user_input(data);
	lexer(data);
	parser(data);
	executor(data);
	free_data_and_restart(data);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (0);
	minishell(init_data());
	return (1);
}
