/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:14:15 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/26 15:15:19 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_data_two(t_data *data);

void	free_data(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	if (data->tokens)
		free_tokens(&data->tokens, free);
	if (data->cmds)
		free_triple_pointer(data->cmds);
	if (data->cmd_paths)
		free_double_pointer(data->cmd_paths);
	if (data->std_input)
		free(data->std_input);
	if (data->std_output)
		free(data->std_output);
	if (data->pipes)
		free_pipes(data, data->pipes);
	free_data_two(data);
}

static void	free_data_two(t_data *data)
{
	if (data->processes)
		free(data->processes);
	if (data->heredoc_delimiters)
		ft_lstclear(&data->heredoc_delimiters, free);
	if (data->heredoc_file)
		unlink(data->heredoc_file);
	if (data->env_paths)
		free_double_pointer(data->env_paths);
	if (data->infile_fd && data->infile_fd > 2)
		close(data->infile_fd);
	if (data->outfile_fd && data->outfile_fd > 2)
		close(data->outfile_fd);
}
