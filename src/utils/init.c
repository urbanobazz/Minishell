/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:25:17 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/25 12:48:15 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environment_paths(t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	path = ft_getenv(data, "PATH");
	if (!path)
	{
		data->env_paths = 0;
		return ;
	}
	data->env_paths = ft_split(path, ':');
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
	data->user_input = 0;
	data->tokens = 0;
	data->cmds = 0;
	data->cmd_paths = 0;
	data->std_input = 0;
	data->std_output = 0;
	data->pipes = 0;
	data->processes = 0;
	data->heredoc_delimiters = 0;
	data->append_mode = 0;
	data->heredoc_file = ".heredoc";
	data->heredoc_mode = 0;
	g_end_heredoc = 0;
	init_environment_paths(data);
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
	data->exit_status = 0;
	return (data);
}
