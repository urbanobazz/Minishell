/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:14:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/24 23:03:41 by louis.demet      ###   ########.fr       */
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
	char	*var;
	char	cwd[1024];

	if (!cmds[1] || ft_strcmp(cmds[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		return (SUCCESS);
	}
	else
	{
		if (chdir(cmds[1]) != 0)
			return (ft_error(data, 5));
	}
	getcwd(cwd, sizeof(cwd));
	var = ft_strjoin("PWD=", cwd);
	if (!var)
		error_and_quit(data, 2);
	export_single_var(data, var);
	free(var);
	return (SUCCESS);
}

int	ft_pwd(t_data *data, char **cmds)
{
	char	cwd[1024];

	if (cmds[1])
		return (ft_error(data, 6));
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
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
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		if (cmds[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (return_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
