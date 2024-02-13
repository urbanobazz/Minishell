/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:14:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/13 18:58:33 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	ft_cd(t_data *data, char **cmds)
{
	if (!cmds[1] || ft_strcmp(cmds[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		return ;
	}
	else if (chdir(cmds[1]) != 0)
		error_and_restart(data, "No such file or directory");
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}

int	find_and_trigger_builtin(t_data *data, char **cmds)
{
	if (cmds[0])
	{
		if (ft_strcmp(cmds[0], "exit") == 0)
			ft_exit(data);
		if (ft_strcmp(cmds[0], "cd") == 0)
			ft_cd(data, cmds);
	}
	return (0);
}
