/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:47 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/24 23:05:51 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_putstr_fd(data->env[i++], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (SUCCESS);
}

int	ft_unset(t_data *data, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		if (!is_name_valid(cmds[i]))
			return (ft_error(data, 4));
		unset_single_var(data, cmds[i]);
		i++;
	}
	return (SUCCESS);
}

int	ft_export(t_data *data, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
		if (!export_single_var(data, cmds[i++]))
			return (FAILURE);
	return (SUCCESS);
}
