/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/25 13:39:35 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_data *data)
{
	if (data)
	{
		if (data->env)
			free_double_pointer(data->env);
		free(data);
	}
}

void	error_and_quit(t_data *data, int err)
{
	ft_error(data, err);
	free_env(data);
	exit(EXIT_FAILURE);
}

void	display_error(int err)
{
	if (err != 10)
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
	else if (err == 8)
		ft_putstr_fd("heredoc delimiter not found\n", STDERR_FILENO);
	else if (err == 9)
		ft_putstr_fd("uneven number of quotes\n", STDERR_FILENO);
	else if (err == 11)
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
	else if (err == 12)
		ft_putstr_fd("execve error\n", STDERR_FILENO);
}

int	ft_error(t_data *data, int err)
{
	data->exit_status = err;
	display_error(err);
	free_data(data);
	return (FAILURE);
}
