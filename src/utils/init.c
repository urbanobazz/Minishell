/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:25:17 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/16 13:41:11 by louis.demet      ###   ########.fr       */
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
		error_and_quit(data, 2);
	while (data->env_paths[i])
	{
		tmp = data->env_paths[i];
		data->env_paths[i] = ft_strjoin(data->env_paths[i], "/");
		if (!data->env_paths[i])
		{
			free(tmp);
			error_and_quit(data, 2);
		}
		free(tmp);
		i++;
	}

}

void	init_env(t_data *data)
{
	extern char	**environ;

	data->env = ft_arrdup(environ);
	if (!data->env)
		error_and_quit(data, 2);
}

void	reset_data(t_data *data)
{
	data->std_input = 0;
	data->std_output = 0;
	data->append_mode = 0;
	data->heredoc_file = ".heredoc";
	data->heredoc_mode = 0;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("Error: Not enough memory to create main data structure\n"\
					, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_env(data);
	init_environment_paths(data);
	data->err_code = 0;
	return (data);
}
