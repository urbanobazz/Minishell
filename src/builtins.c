/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:14:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/13 15:52:34 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	ft_cd(t_data *data, char **cmds)
{
	if (!cmds[1] || chdir(cmds[1]))
		error_and_quit(data);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	find_and_trigger_builtin(t_data *data, char **cmds)
{
	if (ft_strcmp(cmds[0], "exit") == 0)
		ft_exit(data);
	return (0);
}
