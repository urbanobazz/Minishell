/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:12:06 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/26 15:13:28 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens, void (*del)(void*))
{
	t_token	*temp;
	t_token	*next;

	if (!tokens || !del)
		return ;
	temp = *tokens;
	while (temp != NULL)
	{
		next = temp->next;
		(*del)(temp->token);
		free(temp);
		temp = next;
	}
	*tokens = NULL;
}

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_triple_pointer(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free_double_pointer(arr[i++]);
	free(arr);
}

void	free_pipes(t_data *data, int **arr)
{
	int	i;

	i = 0;
	while (i < data->command_count - 1)
		free(arr[i++]);
	if (arr)
		free(arr);
}
