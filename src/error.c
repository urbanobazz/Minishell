/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:19:11 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 12:51:55 by louis.demet      ###   ########.fr       */
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

#include <stdio.h> // Remove after replacing printf with ft_printf
void	handle_error(t_data *data, char *message)
{
	printf("Error: %s\n", message);
	free_data(data);
	exit(EXIT_FAILURE);
}
