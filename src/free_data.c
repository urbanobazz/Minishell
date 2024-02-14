/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:14:15 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/14 16:10:31 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(t_token **tokens, void (*del)(void*));
void		free_double_pointer(char **arr);
static void	free_int_double_pointer(t_data *data, int **arr);
static void	free_triple_pointer(char ***arr);

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->user_input)
			free(data->user_input);
		if (data->tokens)
			free_tokens(&data->tokens, free);
		if (data->cmds)
			free_triple_pointer(data->cmds);
		if (data->cmd_paths)
			free_double_pointer(data->cmd_paths);
		if (data->std_input)
			free(data->std_input);
		if (data->std_output)
			free(data->std_output);
		if (data->pipes)
			free_int_double_pointer(data, data->pipes);
		if (data->env_paths)
			free_double_pointer(data->env_paths);
		if (data->processes)
			free(data->processes);
		if (data->heredoc_delimeter)
			free(data->heredoc_delimeter);
		if (data->heredoc_file)// maybe chnage this to access()
			unlink(data->heredoc_file);
	}
	free(data);
}

static void	free_tokens(t_token **tokens, void (*del)(void*))
{
	t_token	*temp;

	if (!*tokens || !del)
		return ;
	temp = *tokens;
	while (temp != NULL)
	{
		temp = temp -> next;
		(*del)((*tokens)->token);
		*tokens = temp;
	}
	free(*tokens);
}

void	free_double_pointer(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
static void	free_triple_pointer(char ***arr)
{
	int i;

	i = 0;
	while (arr[i])
		free_double_pointer(arr[i++]);
	free(arr);
}

static void	free_int_double_pointer(t_data *data, int **arr)
{
	int i;

	i = 0;
	while (i < data->command_count - 1)
		free(arr[i++]);
	free(arr);
}
