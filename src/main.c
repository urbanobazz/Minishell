/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/15 19:39:25 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	get_user_input(t_data *data)
{
	
	data->user_input = readline("minishell: ");
	if (!data->user_input)
		return (0);
	add_history(data->user_input);
	return (1);
}

void	minishell(t_data *data)
{
	while (1)
	{
		reset_data(data);
		if (!get_user_input(data))
			break ;
		lexer(data);
		if (!parser(data))
			continue ;
		if (!executor(data))
			continue ;
		free_data(data);
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (0);
	minishell(init_data());
	return (1);
}
