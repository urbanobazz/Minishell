/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:57:08 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/16 13:27:41 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredoc_delimiter(t_data *data, t_token *token_list)
{
	if (token_list->next)
		data->heredoc_delimiter = ft_strdup(token_list->next->token);
	else
		error_and_quit(data, 8);
}
void	write_heredoc(t_data *data)
{
	char	*line;
	int		fd;

	data->heredoc_mode = 1;
	fd = open(data->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_and_quit(data, 5);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			error_and_quit(data, 3);
		}
		if (!ft_strcmp(line, data->heredoc_delimiter))
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
