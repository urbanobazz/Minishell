/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/26 17:17:38 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_next_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && !ft_iswhitespace(str[i]) && !is_operator(str[i]))
		i++;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

void	toggle_quote_state(char c, int *sq, int *dq)
{
	if (c == SGL_QUOTE && !(*dq))
		*sq = !(*sq);
	else if (c == DBL_QUOTE && !(*sq))
		*dq = !(*dq);
}

int	is_str_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_iswhitespace(*str))
			return (NO);
		str++;
	}
	return (YES);
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
	while (i < ft_strlen(str) && !is_str_whitespace(str + i))
	{
		len = 0;
		while (ft_iswhitespace(str[i]))
			i++;
		while ((!is_operator(str[i + len]) || sq || dq) && str[i + len])
			toggle_quote_state(str[i + len++], &sq, &dq);
		process_segment(data, str, &i, len);
	}
	if (sq || dq)
		return (ft_error(data, 9));
	return (SUCCESS);
}
