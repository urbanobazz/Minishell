/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/16 13:25:26 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_pipes(t_data *data)
{
	int i;

	i = 0;
	data->pipes = (int **)malloc(sizeof(int *) * data->command_count - 1);
	while (i < data->command_count - 1)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			error_and_quit(data, 2);
		pipe(data->pipes[i]);
		i++;
	}
}

int init_redirections(t_data *data)
{
	if (data->heredoc_mode)
		data->infile_fd = open(data->heredoc_file, O_RDONLY);
	else if (data->std_input)
		data->infile_fd = open(data->std_input, O_RDONLY);
	else
		data->infile_fd = 0;
	if (data->std_output && data->append_mode)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (data->std_output)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->outfile_fd = 1;
	if (data->infile_fd == -1 || data->outfile_fd == -1)
		return (ft_error(data, 5));
	return (SUCCESS);
}

void execute_cmd(t_data *data, int i, int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	execve(data->cmd_paths[i], data->cmds[i], NULL);
}

void execute_shell_command_with_redirection(t_data *data, int i)
{
	int infile_fd;
	int outfile_fd;

	if (i == 0)
		infile_fd = data->infile_fd;
	else
	{
		infile_fd = data->pipes[i - 1][0];
		close(data->pipes[i - 1][1]);
	}
	if (i == data->command_count - 1)
		outfile_fd = data->outfile_fd;
	else
	{
		outfile_fd = data->pipes[i][1];
		close(data->pipes[i][0]);
	}
	execute_cmd(data, i, infile_fd, outfile_fd);
}

void fork_subprocess(t_data *data, int i)
{
	data->processes[i] = fork();
	if (data->processes[i] == 0)
		execute_shell_command_with_redirection(data, i);
	else if (data->processes[i] < 0)
		error_and_quit(data, 2);
	else
	{
		if (i > 0)
			close(data->pipes[i - 1][0]);
		if (i != data->command_count - 1)
			close(data->pipes[i][1]);
	}
}

int run_subprocesses(t_data *data)
{
	int i;
	int ret;

	i = 0;
	data->processes = (pid_t *)malloc(sizeof(pid_t) * data->command_count);
	if (!data->processes)
		error_and_quit(data, 2);
	while (i < data->command_count)
	{
		ret = find_and_trigger_builtin(data, data->cmds[i]);
		if (!ret)
			return (FAILURE);
		if (ret == NOT_BUILTIN)
			fork_subprocess(data, i);
		i++;
	}
	return (SUCCESS);
}

void wait_for_subprocesses(t_data *data)
{
	int i;

	i = 0;
	while (i < data->command_count)
		waitpid(data->processes[i++], NULL, 0);
}

int executor(t_data *data)
{
	init_pipes(data);
	if (!init_redirections(data))
		return (FAILURE);
	if (!run_subprocesses(data))
		return (FAILURE);
	wait_for_subprocesses(data);
	return (SUCCESS);
}
