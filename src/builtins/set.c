/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:31:09 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/16 12:52:27 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_single_var(t_data *data, char *cmd, char *var)
{
	char **new;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_arrlen(data->env) + !ft_getenv(data, var) + 1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		error_and_quit(data, 2);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var, ft_strlen(var)))
			new[j++] = ft_strdup(cmd);
		else
			new[j++] = ft_strdup(data->env[i]);
		i++;
	}
	if (j == len - 2)
		new[j++] = ft_strdup(cmd);
	new[j] = 0;
	free_double_pointer(data->env);
	data->env = new;
}

int export_single_var(t_data *data, char *cmd)
{
	char *eq;
	char *var;

	eq = ft_strchr(cmd, '=');
	if (eq)
	{
		var = ft_substr(cmd, 0, eq - cmd);
		if (!var)
			error_and_quit(data, 2);
		if (!is_name_valid(var))
			return (ft_error(data, 4));
		set_single_var(data, cmd, var);
		free(var);
	}
	return (SUCCESS);
}

char *ft_getenv(t_data *data, char *cmd)
{
	int i;
	char *eq;

	i = 0;
	while (data->env[i])
	{
		eq = strchr(data->env[i], '=');
		if (ft_strncmp(data->env[i], cmd, eq - data->env[i]) == 0)
			return (eq + 1);
		i++;
	}
	return (FAILURE);
}

int is_name_valid(char *cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return (NO);
	if (ft_isdigit(cmd[0]))
		return (NO);
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

void unset_single_var(t_data *data, char *cmd)
{
	char **new;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_arrlen(data->env) - (ft_getenv(data, cmd) != 0) + 1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		error_and_quit(data, 2);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], cmd, ft_strlen(cmd)) == 0)
			i++;
		else
			new[j++] = ft_strdup(data->env[i++]);
	}
	new[i] = 0;
	free_double_pointer(data->env);
	data->env = new;
}
