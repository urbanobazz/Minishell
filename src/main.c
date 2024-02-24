/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:56:37 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/24 20:56:41 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_heredoc;

int	get_user_input(t_data *data)
{
	interactive_signals();
	data->user_input = readline("minishell: ");
	if (!data->user_input)
	{
		write(1, "exit\n", 5);
		return (ft_error(data, 10));
	}
	non_interactive_signals();
	add_history(data->user_input);
	return (SUCCESS);
}

void	minishell(t_data *data)
{
	while (1)
	{
		reset_data(data);
		if (!get_user_input(data))
			break ;
		if (!lexer(data))
			continue ;
		if (!parser(data))
			continue ;
		if (!executor(data))
			continue ;
		free_data(data);
	}
	free_env(data);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	minishell(init_data());
	return (EXIT_SUCCESS);
}
