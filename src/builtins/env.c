/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:47 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 20:20:42 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		ft_printf("%s\n", data->env[i++]);
	return (1);
}

int	ft_unset(t_data *data, char **cmds)
{
	int	i;

	i = 1;
	while(cmds[i])
	{
		if (!is_valid_name(cmds[i]))
			return (ft_error(data, "Invalid variable name"));
		unset_single_var(data, cmds[i]);
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, char **cmds)
{
	int		i;

	i = 1;
	while(cmds[i])
		if (!export_single_var(data, cmds[i++]))
			return (0);
	return (1);
}
