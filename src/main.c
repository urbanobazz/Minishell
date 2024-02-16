/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/16 17:02:12 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_user_input(t_data *data)
{
	interactive_signals();
	data->user_input = readline("minishell: ");
	if (!data->user_input)
	{
		write(1, "Exit\n", 5);
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
