/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/10 17:50:26 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void lexer(t_data *data)
{
	int i;
	int len;

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
