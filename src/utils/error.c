/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/16 12:55:41 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_data *data)
{
	if (data)
	{
		if (data->env)
			free_double_pointer(data->env);
		if (data->env_paths)
			free_double_pointer(data->env_paths);
		free(data);
	}
}

void	error_and_quit(t_data *data, int err)
{
	ft_error(data, err);
	free_env(data);
	exit(EXIT_FAILURE);
}

int	ft_error(t_data *data, int err)
{
	data->err_code = err;
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err == 1)
		ft_putstr_fd("unspecified error\n", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("unable to allocate memory\n", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd("heredoc error\n", STDERR_FILENO);
	else if (err == 4)
		ft_putstr_fd("invalid variable name\n", STDERR_FILENO);
	else if (err == 5)
		ft_putstr_fd("file or directory not found\n", STDERR_FILENO);
	else if (err == 6)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (err == 7)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else
		ft_putstr_fd("unknown error\n", STDERR_FILENO);
	free_data(data);
	return (FAILURE);
}
