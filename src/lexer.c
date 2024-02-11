/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 17:16:52 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_quote_state(char c, int *sq, int *dq)
{
	if (c == SGL_QUOTE && !(*dq))
		*sq = !(*sq);
	else if (c == DBL_QUOTE && !(*sq))
		*dq = !(*dq);
}

void	process_segment(t_data *data, char *str, int *i, int len)
{
	create_token(data, ft_substr(str, *i, len));
	*i += len;
	if (is_operator(str[*i]))
	{
		if (is_operator(str[*i + 1]))
			create_token(data, ft_substr(str, (*i)++, 2));
		else
			create_token(data, ft_substr(str, *i, 1));
	}
}

void	lexer(t_data *data)
{
	int		len;
	char	*str;
	int		i;
	int		sq;
	int		dq;
	
	i = 0;
	sq = 0;
	dq = 0;
	str = data->user_input;
	while (str[i])
	{
		len = 0;
		while ((!is_operator(str[i + len]) || sq || dq) && str[i + len])
		{
			toggle_quote_state(str[i + len], &sq, &dq);
			len++;
		}
		process_segment(data, str, &i, len);
		i++;
	}
}
