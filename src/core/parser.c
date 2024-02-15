/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:25 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 19:33:28 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command_array(t_data *data)
{
	t_token *token_list;
	int not_command_count;

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
			find_heredoc_delimeter(data, token_list);
		else if (token_list->token[0] == '>' && token_list->token[1] == '>')
			data->append_mode = 1;
		token_list = token_list->next;
	}
	data->command_count -= not_command_count;
	data->cmds = (char ***)malloc(sizeof(char **) * data->command_count + 1);
	data->cmd_paths = (char **)malloc(sizeof(char *) * data->command_count + 1);
	if (!data->cmds || !data->cmd_paths)
		error_and_quit(data, "Not enough memory to create commands array");
}

char	**split_commands(char *str, t_data *data)
{
	char	**arr;

	arr = split_skip_quotes(str, ' ');
	if (!arr)
		error_and_quit(data, "Not enough memory to split commands");
	return (arr);
}

void	split_and_store_commands(t_data *data)
{
	t_token *token_list;
	int i;

	token_list = data->tokens;
	i = 0;
	while (token_list)
	{
		if (is_operator(token_list->token[0]))
		{
			if (token_list->token[0] == '|')
				data->cmds[i++] = split_commands(token_list->next->token, data);
			else if (token_list->token[0] == '<' && token_list->token[1] == '<')
				write_heredoc(data);
			else if (token_list->token[0] == '<')
				data->std_input = ft_strdup(token_list->next->token);
			else if (token_list->token[0] == '>')
				data->std_output = ft_strdup(token_list->next->token);
			token_list = token_list->next;
		}
		else
			data->cmds[i++] = split_commands(token_list->token, data);
		token_list = token_list->next;
	}
	data->cmds[i] = 0;
}

int	find_command_paths(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->command_count)
	{
		j = 0;
		while (data->env_paths[j])
		{
			data->cmd_paths[i] = ft_strjoin(data->env_paths[j], data->cmds[i][0]);
			if (!data->cmd_paths[i])
				error_and_quit(data, "Not enough memory to create command path");
			if (access(data->cmd_paths[i], X_OK) == 0)
				break;
			free(data->cmd_paths[i]);
			data->cmd_paths[i] = 0;
			j++;
		}
		if (!data->cmd_paths[i] && !is_builtin(data->cmds[i][0]))
			return (ft_error(data, "Command not found"));
		i++;
	}
	data->cmd_paths[i] = 0;
	return (1);
}

int	parser(t_data *data)
{
	init_command_array(data);
	split_and_store_commands(data);
	expand_variables_and_remove_quotes(data);
	return (find_command_paths(data));
}
