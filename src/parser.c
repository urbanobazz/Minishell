/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:25 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 11:48:17 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	init_command_array(t_data *data)
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
		token_list = token_list->next;
	}
	data->command_count -= not_command_count;
	data->commands = (char **)malloc(sizeof(char *) * data->command_count);
	data->command_paths = (char **)malloc(sizeof(char *) * data->command_count);
	if (!data->commands || !data->command_paths)
		handle_error(data, "Not enough memory to create commands array");
}

void	parser(t_data *data)
{
	t_token	*token_list;
	int		i;

	init_command_array(data);
	token_list = data->tokens;
	i = 0;
	while (token_list)
	{
		if (is_operator(token_list->token[0]))
		{
			if (token_list->token[0] == '|')
				data->commands[i++] = token_list->next->token;
			else if (token_list->token[0] == '<')
				data->std_input = token_list->next->token;
			else if (token_list->token[0] == '>')
				data->std_output = token_list->next->token;
			token_list = token_list->next;
		}
		else
			data->commands[i++] = token_list->token;
		token_list = token_list->next;
	}
}
