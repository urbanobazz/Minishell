/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/08 20:00:26 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_lstlast(t_token *lst)
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

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	*new_token(t_data *data, char *token)
{
	t_token *token;
	
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		handle_error(data);
	ft_lstadd_last(&data->tokens, token);
}

int is_separator(char c)
{
	return (c == '|' || c == '<' || c =='>' );
}

void lexer(t_data *data)
{
	int	start;
	int	length;

	start = 0;
	while (data->user_input[start])
	{
		length = 0;
		while (!is_separator(data->user_input[start + length]) && data->user_input[start + length])
			length++;
		new_token(data, ft_substr(data->user_input, start, length - 1));
		start += length;
		if (is_separator(data->user_input[start]))
			new_token(data, ft_substr(data->user_input, start, 1));
		start++;
	}
}
