/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:47 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 11:50:20 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	extern char **environ;
	int			i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
	return (1);
}

