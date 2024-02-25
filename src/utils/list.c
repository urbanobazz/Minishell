/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:48:44 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/24 21:06:09 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*get_last_token(t_token *lst)
{
	t_token	*last;

	last = lst;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	add_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = get_last_token(*lst);
	last->next = new;
}

void	create_token(t_data *data, char *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_and_quit(data, 2);
	new->token = ft_strtrim(token, " \t\n\v\f\r");
	if (!new->token)
		error_and_quit(data, 2);
	new->next = 0;
	free(token);
	add_token(&data->tokens, new);
}

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

char	**split_commands(char *str, t_data *data)
{
	char	**arr;

	arr = split_skip_quotes(str, ' ');
	if (!arr)
		error_and_quit(data, 2);
	return (arr);
}
