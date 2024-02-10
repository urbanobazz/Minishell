/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:18:42 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 16:31:17 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environment_paths(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	data->env_paths = ft_split(getenv("PATH"), ':');
	if (!data->env_paths)
		error_and_quit(data, "Not enough memory to create environment paths array");
	while (data->env_paths[i])
	{
		tmp = data->env_paths[i];
		data->env_paths[i] = ft_strjoin(data->env_paths[i], "/");
			if (!data->env_paths[i])
				error_and_quit(data, "Not enough memory to create environment path");
		free(tmp);
		i++;
	}

}

t_data	*init_data()
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_and_quit(data, "Not enough memory to create main data structure");
	init_environment_paths(data);
	data->std_input = 0;
	data->std_output = 0;
	return (data);
}

void	get_user_input(t_data *data)
{
	data->user_input = readline("minishell: ");
	if (data->user_input && ft_strcmp(data->user_input, "exit") == 0)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
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
