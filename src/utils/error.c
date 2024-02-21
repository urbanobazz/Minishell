/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piuser <piuser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/21 20:41:11 by piuser           ###   ########.fr       */
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

int	ft_error(t_data *data, int err)
{
	data->exit_status = err;
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
	free_data(data);
	return (FAILURE);
}
