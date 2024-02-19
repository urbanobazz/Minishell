/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:57:08 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/19 18:48:31 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_heredoc_delimiter(t_data *data, t_token *token_list)
{
	t_list *new;

	if (token_list->next)
	{
		new = ft_lstnew(strdup(token_list->next->token));
		ft_lstadd_back(&data->heredoc_delimiters, new);
	}
	else
		error_and_quit(data, 8);
}

int is_delimiter(t_data *data, char *str)
{
	t_list *temp;
	char *delimiter;

	temp = data->heredoc_delimiters;
	delimiter = temp->content;
	if (str[0] == '\n')
		return (0);
	if (!ft_strncmp(str, delimiter, ft_strlen(str) - 1))
	{
		data->heredoc_delimiters = temp->next;
		ft_lstdelone(temp, free);
		return (1);
	}
	else
		return (0);
}

int write_heredoc(t_data *data)
{
	char *line;
	int fd;

	data->heredoc_mode = 1;
	fd = open(data->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_and_quit(data, 5);
	heredoc_interrupt_signal();
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!line || end_heredoc)
		{
			close(fd);
			non_interactive_signals();
			write(1, "\n", 1);
			return (ft_error(data, 10));
		}
		if (is_delimiter(data, line))
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		free(line);
	}
	non_interactive_signals();
	close(fd);
	return (SUCCESS);
}
