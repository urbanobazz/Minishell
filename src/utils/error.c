/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 19:39:07 by louis.demet      ###   ########.fr       */
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

int	ft_error(t_data *data, char *message)
{
	ft_printf("Error: %s\n", message);
	free_data(data);
	return (0);
}

void	error_and_quit(t_data *data, char *message)
{
	ft_printf("Error: %s\n", message);
	free_data(data);
	free_env(data);
	exit(EXIT_FAILURE);
}
