/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:25 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/26 18:32:08 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_command_array(t_data *data)
{
	if (!count_commands(data))
		return (FAILURE);
	data->cmds = (char ***)ft_calloc(sizeof(char **), data->command_count + 1);
	data->cmd_paths = (char **)ft_calloc(sizeof(char *), \
													data->command_count + 1);
	if (!data->cmds || !data->cmd_paths)
		error_and_quit(data, 2);
	return (SUCCESS);
}

void	handle_output_redirection(t_data *data, t_token **token_list)
{
	if (data->std_output)
		free(data->std_output);
	data->std_output = ft_strdup((*token_list)->next->token);
	if ((*token_list)->token[1] == '>')
		data->outfile_fd = open(data->std_output, O_CREAT | \
		O_WRONLY | O_APPEND, 0644);
	else
		data->outfile_fd = open(data->std_output, O_CREAT | \
		O_WRONLY | O_TRUNC, 0644);
	close(data->outfile_fd);
}

int	handle_operator(t_data *data, t_token **token_list, int *i)
{
	if (!token_list || !*token_list)
		return (FAILURE);
	if ((*token_list)->token[0] == '|')
		;
	else if ((*token_list)->token[0] == '<' && (*token_list)->token[1] == '<'
		&& !write_heredoc(data))
		return (FAILURE);
	else if ((*token_list)->token[0] == '<' && (*token_list)->next)
		data->std_input = ft_strdup((*token_list)->next->token);
	else if ((*token_list)->token[0] == '>' && (*token_list)->next)
		handle_output_redirection(data, token_list);
	else
		data->cmds[(*i)++] = split_commands((*token_list)->token, data);
	if (((*token_list)->token[0] == '>' || (*token_list)->token[0] == '<')
		&& (*token_list)->next)
		*token_list = (*token_list)->next;
	return (SUCCESS);
}

int	split_and_store_commands(t_data *data)
{
	t_token	*token_list;
	int		i;

	token_list = data->tokens;
	i = 0;
	while (token_list)
	{
		if (is_operator(token_list->token[0]))
		{
			if (!handle_operator(data, &token_list, &i))
				return (FAILURE);
		}
		else
			data->cmds[i++] = split_commands(token_list->token, data);
		token_list = token_list->next;
	}
	data->cmds[i] = 0;
	return (SUCCESS);
}

int	parser(t_data *data)
{
	if (!init_command_array(data))
		return (FAILURE);
	if (!split_and_store_commands(data))
		return (FAILURE);
	expand_variables_and_remove_quotes(data);
	return (find_command_paths(data));
}
