/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:14:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/14 22:35:47 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data)
{
	free_data(data);
	free_env(data);
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

