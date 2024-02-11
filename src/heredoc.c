/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:57:08 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/11 18:36:21 by ubazzane         ###   ########.fr       */
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
char	*get_heredoc_content(t_data *data)
{
	char	*line;
	char	*temp;
	char	*heredoc_content;

	heredoc_content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
			error_and_quit(data, "Heredoc content not found");
		if (!ft_strcmp(line, data->heredoc_delimeter))
			break;
		temp = ft_strjoin(heredoc_content, "\n");
		free(heredoc_content);
		heredoc_content = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	//ft_printf("heredoc content: %s$\n", heredoc_content); // debug
	return (heredoc_content);
}
