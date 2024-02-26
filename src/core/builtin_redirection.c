/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:29 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/26 15:39:03 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	backup_redirection(t_data *data, int i, int io[2], int tmp_fd[2])
{
	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (tmp_fd[0] == -1 || tmp_fd[1] == -1)
		return (FAILURE);
	get_input_output(data, i, io);
	if (io[0] != STDIN_FILENO && dup2(io[0], STDIN_FILENO) == -1)
		error_and_quit(data, 11);
	if (io[1] != STDOUT_FILENO && dup2(io[1], STDOUT_FILENO) == -1)
		error_and_quit(data, 11);
	return (SUCCESS);
}

void	restore_redirection(t_data *data, int i, int io[2], int tmp_fd[2])
{
	if (i > 0)
		close(data->pipes[i - 1][0]);
	if (i < data->command_count - 1)
		close(data->pipes[i][1]);
	if (io[0] != STDIN_FILENO && dup2(tmp_fd[0], STDIN_FILENO) == -1)
		error_and_quit(data, 11);
	if (io[1] != STDOUT_FILENO && dup2(tmp_fd[1], STDOUT_FILENO) == -1)
		error_and_quit(data, 11);
	if (io[0] > 2)
		close(io[0]);
	if (io[1] > 2)
		close(io[1]);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}
