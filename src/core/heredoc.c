/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:57:08 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/18 18:18:23 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_heredoc_delimiter(t_data *data, t_token *token_list)
{
	t_list	*new;

	if (token_list->next)
	{
		new = ft_lstnew(strdup(token_list->next->token));
		ft_lstadd_back(&data->heredoc_delimiters, new);
	}
	else
		error_and_quit(data, 8);
}

int is_delimeter(t_data *data, char *str)
{
	t_list	*temp;
	char	*delimiter;

	temp = data->heredoc_delimiters;
	delimiter = temp->content;
	if (!ft_strcmp(str, delimiter))
	{
		data->heredoc_delimiters = temp->next;
		ft_lstdelone(temp, free);
		return (1);
	}
	else
		return (0);
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
		interactive_signals();
		line = readline("> ");
		if (!line)
		{
			close(fd);
			error_and_quit(data, 3);//Must restart the shell.
		}
		non_interactive_signals();
		if (is_delimeter(data, line))
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
