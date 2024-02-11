/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 11:33:05 by louis.demet      ###   ########.fr       */
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
	int	single_quote_open;
	int	double_quote_open;

	i = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while (data->user_input[i])
	{
		len = 0;
		while ((!is_operator(data->user_input[i + len]) || single_quote_open || double_quote_open) && data->user_input[i + len])
		{
			if (data->user_input[i + len] == SINGLE_QUOTE && !double_quote_open)
				single_quote_open = !single_quote_open;
			else if (data->user_input[i + len] == DOUBLE_QUOTE && !single_quote_open)
				double_quote_open = !double_quote_open;
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
