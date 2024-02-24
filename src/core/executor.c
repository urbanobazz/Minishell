/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/24 12:31:05 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_pipes(t_data *data)
{
	int i = 0;
	if (data->command_count <= 0)
		return;
	data->pipes = (int **)malloc(sizeof(int *) * (data->command_count - 1));
	if (!data->pipes)
		error_and_quit(data, 11);
	while (i < data->command_count - 1)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			error_and_quit(data, 2);
		if (pipe(data->pipes[i]) == -1)
		{
			error_and_quit(data, 11);
		}
		printf("1: Created pipe %d: read end = %d, write end = %d\n", i, data->pipes[i][0], data->pipes[i][1]);
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
		data->infile_fd = STDIN_FILENO;
	if (data->std_output && data->append_mode)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (data->std_output)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->outfile_fd = STDOUT_FILENO;
	if (data->infile_fd == -1 || data->outfile_fd == -1)
		return (ft_error(data, 5));
	return (SUCCESS);
}

void close_all_pipes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->command_count - 1)
	{
		if (data->pipes[i][0] > 2)
			close(data->pipes[i][0]);
		if (data->pipes[i][0] > 2)
			close(data->pipes[i][1]);
		i++;
	}
}

void execute_cmd(t_data *data, int i, int input_fd, int output_fd)
{
	printf("4: in subprocess pid %i, preparing for execution, STDIN: %i, STDOUT: %i\n", getpid(), input_fd, output_fd);
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("[execute_cmd] dup2 input_fd failed");
			exit(EXIT_FAILURE);
		}
		printf("5: in subprocess pid %i, duplicated fd %i\n", getpid(), input_fd);
		// printf("6: in subprocess pid %i, closed fd %i\n", getpid(), input_fd);
		// close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("[execute_cmd] dup2 output_fd failed");
			exit(EXIT_FAILURE);
		}
		printf("5: in subprocess pid %i, duplicated fd %i\n", getpid(), output_fd);
		// printf("6: in subprocess pid %i, closed fd %i\n", getpid(), output_fd);
		// close(output_fd);
	}
	printf("7: in subprocess pid %i executing command with execve: %s, STDIN: %d, STDOUT: %d\n", getpid(), data->cmds[i][0], STDIN_FILENO, STDOUT_FILENO);
	close_all_pipes(data);
	execve(data->cmd_paths[i], data->cmds[i], data->env);
	// Note: If execve returns, it has failed
	error_and_quit(data, 12);
}

void execute_shell_command_with_redirection(t_data *data, int i)
{
	int infile_fd, outfile_fd;

	if (i == 0)
		infile_fd = data->infile_fd;
	else
	{
		infile_fd = data->pipes[i - 1][0];
		printf("3s: In subprocess pid %i, closed fd %i\n", getpid(), data->pipes[i - 1][1]);
		close(data->pipes[i - 1][1]);
	}
	if (i == data->command_count - 1)
		outfile_fd = data->outfile_fd;
	else
	{
		outfile_fd = data->pipes[i][1];
		printf("3s: In subprocess pid %i, closed fd %i\n", getpid(), data->pipes[i][0]);
		close(data->pipes[i][0]);
	}
	execute_cmd(data, i, infile_fd, outfile_fd);
}

void fork_subprocess(t_data *data, int i)
{
	data->processes[i] = fork();
	if (data->processes[i] == 0) // Child process
	{
		printf("2s: Starting subprocess pid %d for command %d\n", getpid(), i);
		execute_shell_command_with_redirection(data, i);
	}
	else if (data->processes[i] < 0)
		error_and_quit(data, 11);
	else // Parent process
	{
		printf("2m: In main process pid %i, forked subprocess pid %d for command %d\n", getpid(), data->processes[i], i);
		// Close pipe ends in the parent as soon as they are no longer needed
		if (i > 0)
		{
			printf("3m: In main process pid %i, closed fd %i\n", getpid(), data->pipes[i - 1][0]);
			close(data->pipes[i - 1][0]);
		}
		if (i != data->command_count - 1)
		{
			printf("3m: In main process pid %i, closed fd %i\n", getpid(), data->pipes[i][1]);
			close(data->pipes[i][1]);
		}
	}
}

int run_subprocesses(t_data *data)
{
	int i;
	int ret;

	i = 0;
	data->processes = ft_calloc(sizeof(pid_t), data->command_count);
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
	int i = 0, status = 0;
	while (i < data->command_count)
	{
		waitpid(data->processes[i++], &status, 0);
		printf("8: Process %d (PID: %d) exited with status %d\n", i, data->processes[i], WEXITSTATUS(status));
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
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
