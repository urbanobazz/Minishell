/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:57:08 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/15 18:53:42 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredoc_delimeter(t_data *data, t_token *token_list)
{
	if (token_list->next)
		data->heredoc_delimeter = ft_strdup(token_list->next->token);
	else
		error_and_quit(data, "No heredoc delimeter found");
}
void	write_heredoc(t_data *data)
{
	char	*line;
	int		fd;

	data->heredoc_mode += 1;
	fd = open(data->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_and_quit(data, "Failed to open heredoc file for writing");
	while (1)
	{
		interactive_signals();
		line = readline("> ");
		if (!line)
		{
			close(fd);
			error_and_quit(data, "Heredoc content not found");
		}
		non_interactive_signals();
		if (!ft_strcmp(line, data->heredoc_delimeter))
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
