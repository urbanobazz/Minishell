/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:47 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 12:20:27 by louis.demet      ###   ########.fr       */
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

char	*ft_getenv(t_data *data, char *cmd)
{
	int			i;
	char		*eq;

	i = 0;
	while (data->env[i])
	{
		eq = strchr(data->env[i], '=');
		if (ft_strncmp(data->env[i], cmd, eq - data->env[i]) == 0)
			return (eq + 1);
		i++;
	}
	return (0);
}

int	is_env_match(t_data *data, char *cmd)
{
	int			i;
	char		*eq;

	i = 0;
	while (data->env[i])
	{
		eq = strchr(data->env[i], '=');
		if (ft_strncmp(data->env[i], cmd, eq - data->env[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_name(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	if (ft_isdigit(cmd[0]))
		return (0);
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
		if (ft_strncmp(data->env[i], cmd, ft_strlen(cmd)) == 0)
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
	{
		if (!is_valid_name(cmds[i]))
			error_and_restart(data, "Invalid variable name");
		unset_single_var(data, cmds[i]);
		i++;
	}
	return (1);
}

void	set_single_var(t_data *data, char *cmd, char *var)
{
	char		**new;
	int			len;
	int			i;
	int			j;

	i = 0;
	j = 0;
	len = ft_arrlen(data->env) + !is_env_match(data, var) + 1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		error_and_quit(data, "Not enough memory for environment variables");
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

void	export_single_var(t_data *data, char *cmd)
{
	char	*eq;
	char	*var;

	eq = ft_strchr(cmd, '=');
	if (eq)
	{
		var = ft_substr(cmd, 0, eq - cmd);
		if (!var)
			error_and_quit(data, "Not enough data for environment variables");
		if (!is_valid_name(var))
			error_and_restart(data, "Invalid variable name");
		set_single_var(data, cmd, var);
		free(var);
	}
}

int	ft_export(t_data *data, char **cmds)
{
	int		i;

	i = 1;
	while(cmds[i])
		export_single_var(data, cmds[i++]);
	return (1);
}
