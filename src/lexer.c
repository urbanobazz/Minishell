/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 11:13:42 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void lexer(t_data *data)
{
	int	i;
	int	len;
	int	quote_open;

	i = 0;
	quote_open = 0;
	while (data->user_input[i])
	{
		len = 0;
		while ((!is_operator(data->user_input[i + len]) || quote_open) && data->user_input[i + len])
		{
			if (data->user_input[i + len] == DOUBLE_QUOTE || data->user_input[i + len] == SINGLE_QUOTE)
				quote_open = !quote_open;
			len++;
		}
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
