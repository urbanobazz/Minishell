/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:31 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 11:05:41 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
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
			return (ft_cd(data, cmds));
		if (ft_strcmp(cmds[0], "pwd") == 0)
			return (ft_pwd(data, cmds));
		if (ft_strcmp(cmds[0], "echo") == 0)
			return (ft_echo(cmds));
	}
	return (0);
}
