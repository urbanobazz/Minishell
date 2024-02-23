/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piuser <piuser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/23 13:19:46 by piuser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_pipes(t_data *data)
{
	int i = 0;
	if (data->command_count <= 0)
		return ;
	data->pipes = (int **)malloc(sizeof(int *) * (data->command_count - 1));
	if (!data->pipes)
		error_and_quit(data, 11);
	while (i < data->command_count - 1)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			error_and_quit(data, 2);
		if (pipe(data->pipes[i]) == -1) {
			error_and_quit(data, 11);
		}
		printf("[init_pipes] Created pipe %d: read end = %d, write end = %d\n", i, data->pipes[i][0], data->pipes[i][1]);
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
		if (dup2(input_fd, STDIN_FILENO) == -1) {
			perror("[execute_cmd] dup2 input_fd failed");
			exit(EXIT_FAILURE);
		}
		printf("In PID %i, closed fd %i\n", getpid(), input_fd);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1) {
			perror("[execute_cmd] dup2 output_fd failed");
			exit(EXIT_FAILURE);
		}
		printf("In PID %i, closed fd %i\n", getpid(), output_fd);
		close(output_fd);
	}
	printf("[execute_cmd] Executing command with execve: %s, STDIN: %d, STDOUT: %d\n", data->cmds[i][0], input_fd, output_fd);
	execve(data->cmd_paths[i], data->cmds[i], NULL);
	// Note: If execve returns, it has failed
	perror("[execute_cmd] execve failed");
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
		printf("In PID %i, closed fd %i\n", getpid(), data->pipes[i - 1][1]);
		close(data->pipes[i - 1][1]);
	}
	if (i == data->command_count - 1)
		outfile_fd = data->outfile_fd;
	else
	{
		outfile_fd = data->pipes[i][1];
		printf("In PID %i, closed fd %i\n", getpid(), data->pipes[i][0]);
		close(data->pipes[i][0]);
	}
	printf("[execute_shell_command_with_redirection] Command %d, infile_fd: %d, outfile_fd: %d\n", i, infile_fd, outfile_fd);
	execute_cmd(data, i, infile_fd, outfile_fd);
}


void fork_subprocess(t_data *data, int i)
{
	printf("[fork_subprocess] Forking process for command %d\n", i);
	data->processes[i] = fork();
	if (data->processes[i] == 0) // Child process
	{
		printf("[fork_subprocess] In child process (PID: %d) for command %d\n", getpid(), i);
		execute_shell_command_with_redirection(data, i);
	}
	else if (data->processes[i] < 0)
	{
		perror("[fork_subprocess] Fork failed");
		exit(EXIT_FAILURE);
	}
	else // Parent process
	{
		printf("[fork_subprocess] In parent process (PID: %i), created child process (PID: %d) for command %d\n", getpid(), data->processes[i], i);
		// Close pipe ends in the parent as soon as they are no longer needed
		if (i > 0)
		{
			printf("In PID %i, closed fd %i\n", getpid(), data->pipes[i - 1][0]);
			close(data->pipes[i - 1][0]);
		}
		if (i != data->command_count - 1)
		{
			printf("In PID %i, closed fd %i\n", getpid(), data->pipes[i][1]);
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
		printf("[wait_for_subprocesses] Process %d (PID: %d) exited with status %d\n", i, data->processes[i], WEXITSTATUS(status));
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
