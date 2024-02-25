/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piuser <piuser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:40:34 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/25 21:16:14 by piuser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
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
		if (pipe(data->pipes[i]) == -1)
			error_and_quit(data, 11);
		i++;
	}
}

int	init_redirections(t_data *data)
{
	if (data->heredoc_mode)
		data->infile_fd = open(data->heredoc_file, O_RDONLY);
	else if (data->std_input)
		data->infile_fd = open(data->std_input, O_RDONLY);
	else
		data->infile_fd = STDIN_FILENO;
	if (data->std_output && data->append_mode)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY
				| O_APPEND, 0644);
	else if (data->std_output)
		data->outfile_fd = open(data->std_output, O_CREAT | O_WRONLY
				| O_TRUNC, 0644);
	else
		data->outfile_fd = STDOUT_FILENO;
	if (data->infile_fd == -1)
	{
		perror("Error");
		data->infile_fd = STDIN_FILENO;
	}
	if (data->outfile_fd == -1)
	{
		perror("Error");
		data->infile_fd = STDOUT_FILENO;
	}
	return (SUCCESS);
}

void	close_all_pipes(t_data *data)
{
	int	i;

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

void	get_input_output(t_data *data, int i, int io[2])
{
	if (i == 0)
		io[0] = data->infile_fd;
	else
		io[0] = data->pipes[i - 1][0];
	if (i == data->command_count - 1)
		io[1] = data->outfile_fd;
	else
		io[1] = data->pipes[i][1];
}
