/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/24 20:42:53 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_data *data, int i, int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO && dup2(input_fd, STDIN_FILENO) == -1)
		error_and_quit(data, 11);
	if (output_fd != STDOUT_FILENO && dup2(output_fd, STDOUT_FILENO) == -1)
		error_and_quit(data, 11);
	close_all_pipes(data);
	execve(data->cmd_paths[i], data->cmds[i], data->env);
	error_and_quit(data, 12);
}

void	fork_subprocess(t_data *data, int i)
{
	data->processes[i] = fork();
	if (data->processes[i] == 0)
		execute_shell_command_with_redirection(data, i);
	else if (data->processes[i] < 0)
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
	int	res;

	i = 0;
	data->processes = ft_calloc(sizeof(pid_t), data->command_count);
	if (!data->processes)
		error_and_quit(data, 2);
	while (i < data->command_count)
	{
		res = find_and_trigger_builtin(data, data->cmds[i]);
		if (!res)
			return (FAILURE);
		if (res == NOT_BUILTIN)
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
