/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:36 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/26 15:19:24 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cycle_command_paths(t_data *data, int i)
{
	int	j;

	j = 0;
	free(data->cmd_paths[i]);
	data->cmd_paths[i] = 0;
	while (data->env_paths && data->env_paths[j])
	{
		data->cmd_paths[i] = ft_strjoin(data->env_paths[j], data->cmds[i][0]);
		if (!data->cmd_paths[i])
			error_and_quit(data, 2);
		if (access(data->cmd_paths[i], X_OK) == 0)
			break ;
		free(data->cmd_paths[i]);
		data->cmd_paths[i] = 0;
		j++;
	}
}

int	find_command_paths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->command_count)
	{
		data->cmd_paths[i] = ft_strdup(data->cmds[i][0]);
		if (!data->cmd_paths[i])
			return (ft_error(data, 2));
		if (access(data->cmd_paths[i], X_OK) != 0)
			cycle_command_paths(data, i);
		if (!data->cmd_paths[i] && !is_builtin(data->cmds[i][0]))
			return (ft_error(data, 7));
		i++;
	}
	data->cmd_paths[i] = 0;
	return (SUCCESS);
}
