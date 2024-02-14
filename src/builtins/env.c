/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:47 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 23:30:00 by louis.demet      ###   ########.fr       */
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

int	is_env_match(t_data *data, char *cmd)
{
	int			i;

	i = 0;
	while (data->env[i])
	{
		if (strcmp(data->env[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	unset_single_var(t_data *data, char *cmd)
{
	char		**new;
	int			len;
	int			i;
	int			j;

	i = 0;
	j = 0;
	len = ft_arrlen(data->env) - is_env_match(data, cmd) + 1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		error_and_quit(data, "Not enough memory for environment variables");
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], cmd, ft_strlen(cmd)))
			i++;
		else
			new[j++] = ft_strdup(data->env[i++]);
	}
	new[i] = 0;
	free_double_pointer(data->env);
	data->env = new;
}

int	ft_unset(t_data *data, char **cmds)
{
	int	i;

	i = 1;
	while(cmds[i])
		unset_single_var(data, cmds[i++]);
	return (1);
}
