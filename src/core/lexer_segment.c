/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/26 15:00:09 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_operator(t_data *data, char *str, size_t *i);
void	process_next_word(t_data *data, char *str, size_t *i, int *len);
void	process_remaining_string(t_data *data, char *str, size_t *i, int len);

void	process_segment(t_data *data, char *str, size_t *i, int len)
{
	process_operator(data, str, i);
	process_next_word(data, str, i, &len);
	process_remaining_string(data, str, i, len);
}

void	process_operator(t_data *data, char *str, size_t *i)
{
	if (is_operator(str[*i]))
	{
		if (is_operator(str[*i + 1]))
			create_token(data, ft_substr(str, (*i)++, 2));
		else
			create_token(data, ft_substr(str, *i, 1));
		(*i)++;
	}
}

void	process_next_word(t_data *data, char *str, size_t *i, int *len)
{
	char	*next_word;
	t_token	*last_token;

	last_token = get_last_token(data->tokens);
	if (*len > 0 && last_token && (last_token->token[0] == '>'
			|| last_token->token[0] == '<'))
	{
		next_word = ft_get_next_word(str + *i);
		*i += ft_strlen(next_word);
		*len -= ft_strlen(next_word);
		create_token(data, next_word);
	}
}

void	process_remaining_string(t_data *data, char *str, size_t *i, int len)
{
	if (len > 0)
	{
		create_token(data, ft_substr(str, *i, len));
		*i += len;
	}
}
