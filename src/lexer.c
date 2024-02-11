/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 12:10:00 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void lexer(t_data *data)
{
	int		i;
	int		len;
	int		sq;
	int		dq;
	char	*str;

	i = 0;
	sq = 0;
	dq = 0;
	str = data->user_input;
	while (str[i])
	{
		len = 0;
		while ((!is_operator(str[i + len]) || sq || dq) && str[i + len])
		{
			if (str[i + len] == SINGLE_QUOTE && !dq)
				sq = !sq;
			else if (str[i + len] == DOUBLE_QUOTE && !sq)
				dq = !dq;
			len++;
		}
		create_token(data, ft_substr(str, i, len));
		i += len;
		if (is_operator(str[i]))
		{
			if (is_operator(str[i + 1]))
				create_token(data, ft_substr(str, i++, 2));
			else
				create_token(data, ft_substr(str, i, 1));
		}
		i++;
	}
}
