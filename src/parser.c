/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:25 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 12:14:27 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_command_array(t_data *data)
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
			data->heredoc_mode = 1;
		else if (token_list->token[0] == '>' && token_list->token[1] == '>')
			data->append_mode = 1;
		token_list = token_list->next;
	}
	data->command_count -= not_command_count;
	data->commands = (char ***)malloc(sizeof(char **) * data->command_count);
	data->cmd_paths = (char **)malloc(sizeof(char *) * data->command_count);
	if (!data->commands || !data->cmd_paths)
		error_and_quit(data, "Not enough memory to create commands array");
}

void parse_tokens(t_data *data)
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
				data->commands[i++] = split_skip_quotes(token_list->next->token, ' ');
			else if (token_list->token[0] == '<')
				data->std_input = token_list->next->token;
			else if (token_list->token[0] == '>')
				data->std_output = token_list->next->token;
			token_list = token_list->next;
		}
		else
			data->commands[i++] = split_skip_quotes(token_list->token, ' ');
		token_list = token_list->next;
	}
}

void parse_command_paths(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->command_count)
	{
		j = 0;
		while (data->env_paths[j])
		{
			data->cmd_paths[i] = ft_strjoin(data->env_paths[j], data->commands[i][0]);
			if (!data->cmd_paths[i])
				error_and_quit(data, "Not enough memory to create command path");
			if (access(data->cmd_paths[i], X_OK) == 0)
				break;
			free(data->cmd_paths[i]);
			data->cmd_paths[i] = 0;
			j++;
		}
		if (!data->cmd_paths[i])
			error_and_restart(data, "Command does not exist");
		i++;
	}
}

void parser(t_data *data)
{
	init_command_array(data);
	parse_tokens(data);
	parse_command_paths(data);
}
