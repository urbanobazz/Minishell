/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 19:14:24 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_data(t_data *data)
{
	if (data)
		free(data);
}

void	free_data_and_restart(t_data *data)
{
	free_data(data);
	minishell();
}


void	error_and_restart(t_data *data, char *message)
{
	ft_printf("Error: %s\n", message);
	free_data(data);
	minishell();
}

void	error_and_quit(t_data *data, char *message)
{
	ft_printf("Error: %s\n", message);
	free_data(data);
	exit(EXIT_FAILURE);
}
