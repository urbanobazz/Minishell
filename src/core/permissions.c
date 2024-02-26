/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:04:28 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/26 18:05:37 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_permissions(pid_t *processes, char *cmd, int i)
{
	if (ft_strcmp(cmd, ".") == 0
		|| ft_strcmp(cmd, "..") == 0
		|| ft_strcmp(cmd, "./") == 0)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		processes[i] = -2;
		return (NO);
	}
	return (YES);
}
