/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 16:15:28 by louis.demet      ###   ########.fr       */
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
	t_token *new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		handle_error(data, "Not enough memory to create token");
	new->token = ft_strtrim(token, " ");
	free(token);
	add_token(&data->tokens, new);
}


int	is_operator(char c)
{
	return (c == '|' || c == '<' || c =='>' );
}

void	lexer(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (data->user_input[i])
	{
		len = 0;
		while (!is_operator(data->user_input[i + len]) && data->user_input[i + len])
			len++;
		create_token(data, ft_substr(data->user_input, i, len));
		i += len;
		if (is_operator(data->user_input[i]))
		{
			if (is_operator(data->user_input[i + 1]))
				create_token(data, ft_substr(data->user_input, i++, 2));
			else
				create_token(data, ft_substr(data->user_input, i, 1));
		}
		i++;
	}
}
