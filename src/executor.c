/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:43:43 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/09 15:27:38 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = (int **)malloc(sizeof(int *) * data->command_count - 1);
	while (i < data->command_count - 1)
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			handle_error(data);
		pipe(data->pipes[i]);
		i++;
	}
}

void	init_redirections(t_data *data)
{
	if (data->std_input)
		data->infile_fd = open(data->std_input, O_RDONLY);
	else
		data->infile_fd = 0;
	if (data->std_output)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->outfile_fd = 1;
	if (data->infile_fd == -1 || data->outfile_fd == -1)
		handle_error(data);
}

void execute_cmd(char *cmd, int input_fd, int output_fd)
{
    char *argv[4] = {"/bin/sh", "-c", cmd, NULL};
    char *envp[] = {NULL};

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
	execve("/bin/sh", argv, envp);
}

void	run_subprocesses(t_data *data)
{
	int	i;
	int	infile_fd;
	int outfile_fd;

	i = 0;
	data->processes = (pid_t *)malloc(sizeof(pid_t) * data->command_count);
	if (!data->processes)
		handle_error(data);
	while (i < data->command_count)
	{
		if (i == 0)
			infile_fd = data->infile_fd;
		else
			infile_fd = data->pipes[i - 1][0];
		if (i == data->command_count - 1)
			outfile_fd = data->outfile_fd;
		else
			outfile_fd = data->pipes[i][1];
		data->processes[i] = fork();
		if (data->processes[i] == 0)
			execute_cmd(data->commands[i], infile_fd, outfile_fd);
		else if (data->processes[i] < 0)
			handle_error(data);
		i++;
	}
	i = 0;
	while (i < data->command_count)
		waitpid(data->processes[i++], NULL, 0);
}

void	executor(t_data *data)
{
	init_pipes(data);
	init_redirections(data);
	run_subprocesses(data);
}
