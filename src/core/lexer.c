/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/17 18:31:10 by louis.demet      ###   ########.fr       */
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

void	process_segment(t_data *data, char *str, size_t *i, int len)
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

int	lexer(t_data *data)
{
	int		len;
	char	*str;
	size_t	i;
	int		sq;
	int		dq;
	
	i = 0;
	sq = 0;
	dq = 0;
	str = data->user_input;
	while (i < ft_strlen(str))
	{
		len = 0;
		while ((!is_operator(str[i + len]) || sq || dq) && str[i + len])
			toggle_quote_state(str[i + len++], &sq, &dq);
		if (len > 0)
			process_segment(data, str, &i, len);
		i++;
	}
	if (sq || dq)
		return (ft_error(data, 9));
	return (SUCCESS);
}
