/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:18:42 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 11:25:24 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_user_input(t_data *data)
{
	data->user_input = readline("minishell: ");
	add_history(data->user_input);
}

void	minishell(void)
{
	t_data	*data;

	data = init_data();
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
	minishell();
	return (1);
}
