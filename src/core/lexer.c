/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piuser <piuser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:28 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/22 13:59:57 by piuser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_next_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && ft_isalnum(str[i]))
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

void	process_segment(t_data *data, char *str, size_t *i, int len)
{
	char	*next_word;
	t_token	*last_token;

	next_word = 0;
	if (is_operator(str[*i]))
	{
		if (is_operator(str[*i + 1]))
			create_token(data, ft_substr(str, (*i)++, 2));
		else
			create_token(data, ft_substr(str, *i, 1));
		(*i)++;
	}
	last_token = get_last_token(data->tokens);
	if (len > 0 && last_token && (last_token->token[0] == '>' || last_token->token[0] == '<'))
	{
		next_word = ft_get_next_word(str + *i);
		*i += ft_strlen(next_word);
		len -= ft_strlen(next_word);
		create_token(data, next_word);
	}
	if (len > 0)
	{
		create_token(data, ft_substr(str, *i, len));
		*i += len;
	}
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
		while ((!is_operator(str[i + len]) || sq || dq) && str[i + len])
			toggle_quote_state(str[i + len++], &sq, &dq);
		process_segment(data, str, &i, len);
	}
	if (sq || dq)
		return (ft_error(data, 9));
	return (SUCCESS);
}
