/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:14:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/13 21:40:58 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	ft_cd(t_data *data, char **cmds)
{
	if (!cmds[1] || ft_strcmp(cmds[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (chdir(cmds[1]) != 0)
		error_and_restart(data, "No such file or directory");
	return (1);
}

int	ft_pwd(t_data *data, char **cmds)
{
	char	cwd[1024];

	if (cmds[1])
		error_and_restart(data, "Too many arguments");
	ft_printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (1);
}

int	ft_echo(char **cmds)
{
	int	i;
	int	return_flag;

	i = 0;
	return_flag = 1;
	if (cmds[1] && ft_strcmp(cmds[1], "-n") == 0)
	{
		return_flag = 0;
		i++;
	}
	while (cmds[++i])
	{
		ft_printf(cmds[i]);
		if (cmds[i + 1])
			ft_printf(" ");
	}
	if (return_flag)
		ft_printf("\n");
	return (1);
}

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
