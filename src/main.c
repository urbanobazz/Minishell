/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/16 12:45:39 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_user_input(t_data *data)
{

	data->user_input = readline("minishell: ");
	if (!data->user_input)
		return (FAILURE);
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
		lexer(data);
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
