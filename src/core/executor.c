/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/26 18:03:36 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_data *data, int i)
{
	int	tmp_fd[2];
	int	io[2];

	if (!backup_redirection(data, i, io, tmp_fd))
		return (FAILURE);
	if (!find_and_trigger_builtin(data, data->cmds[i]))
		return (FAILURE);
	restore_redirection(data, i, io, tmp_fd);
	data->exit_status = 0;
	return (SUCCESS);
}

void	fork_subprocess(t_data *data, int i)
{
	int	io[2];

	if (has_permissions(data->processes, data->cmds[i][0], i))
		data->processes[i] = fork();
	if (data->processes[i] == 0)
	{
		get_input_output(data, i, io);
		if (io[0] != STDIN_FILENO && dup2(io[0], STDIN_FILENO) == -1)
			error_and_quit(data, 11);
		if (io[1] != STDOUT_FILENO && dup2(io[1], STDOUT_FILENO) == -1)
			error_and_quit(data, 11);
		close_all_pipes(data);
		execve(data->cmd_paths[i], data->cmds[i], data->env);
		error_and_quit(data, 12);
	}
	else if (data->processes[i] == -1)
		error_and_quit(data, 11);
	else
	{
		if (i > 0)
			close(data->pipes[i - 1][0]);
		if (i != data->command_count - 1)
			close(data->pipes[i][1]);
	}
}

int	run_subprocesses(t_data *data)
{
	int	i;

	i = 0;
	data->processes = ft_calloc(sizeof(pid_t), data->command_count);
	if (!data->processes)
		error_and_quit(data, 2);
	while (i < data->command_count)
	{
		if (is_builtin(data->cmds[i][0]))
		{
			if (!run_builtin(data, i))
				return (FAILURE);
		}
		else
			fork_subprocess(data, i);
		i++;
	}
	return (SUCCESS);
}

void	wait_for_subprocesses(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data->command_count)
	{
		waitpid(data->processes[i++], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}

int	executor(t_data *data)
{
	init_pipes(data);
	if (!init_redirections(data))
		return (FAILURE);
	if (!run_subprocesses(data))
		return (FAILURE);
	wait_for_subprocesses(data);
	return (SUCCESS);
}
