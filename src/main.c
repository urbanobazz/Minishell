/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:18:42 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/09 16:41:25 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data()
{
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		handle_error(data);
	data->std_input = 0;
	data->std_output = 0;
	return (data);
}


void	minishell(void)
{
	t_data	*data;

	while (1)
	{
		data = init_data();
		data->user_input = readline("minishell: ");
		if (data->user_input && ft_strcmp(data->user_input, "exit") == 0)
		{
			free_data(data);
			break;
		}
		lexer(data);
		parser(data);
		executor(data);
		free_data(data);
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (0);
	minishell();
	return (1);
}