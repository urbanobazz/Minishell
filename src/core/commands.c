/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:36 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/26 18:32:12 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cycle_command_paths(t_data *data, int i)
{
	int	j;

	j = 0;
	free(data->cmd_paths[i]);
	data->cmd_paths[i] = 0;
	while (data->env_paths && data->env_paths[j])
	{
		data->cmd_paths[i] = ft_strjoin(data->env_paths[j], data->cmds[i][0]);
		if (!data->cmd_paths[i])
			error_and_quit(data, 2);
		if (access(data->cmd_paths[i], X_OK) == 0)
			break ;
		free(data->cmd_paths[i]);
		data->cmd_paths[i] = 0;
		j++;
	}
}

int	find_command_paths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->command_count)
	{
		data->cmd_paths[i] = ft_strdup(data->cmds[i][0]);
		if (!data->cmd_paths[i])
			return (ft_error(data, 2));
		if (access(data->cmd_paths[i], X_OK) != 0)
			cycle_command_paths(data, i);
		if (!data->cmd_paths[i] && !is_builtin(data->cmds[i][0]))
			return (ft_error(data, 7));
		i++;
	}
	data->cmd_paths[i] = 0;
	return (SUCCESS);
}

int	count_commands(t_data *data)
{
	t_token	*token_list;
	int		not_command_count;

	data->command_count = ft_token_lstsize(data->tokens);
	token_list = data->tokens;
	not_command_count = 0;
	while (token_list)
	{
		if (token_list->token[0] == '|')
			not_command_count++;
		else if (token_list->token[0] == '<' || token_list->token[0] == '>')
			not_command_count += 2;
		if (token_list->token[0] == '<' && token_list->token[1] == '<')
			find_heredoc_delimiter(data, token_list);
		else if (token_list->token[0] == '>' && token_list->token[1] == '>')
			data->append_mode = 1;
		token_list = token_list->next;
	}
	data->command_count -= not_command_count;
	if (data->command_count < 0)
		return (ft_error(data, 7));
	return (SUCCESS);
}
