/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:25:43 by ubazzane          #+#    #+#             */
/*   Updated: 2024/02/25 14:28:36 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str, char **output)
{
	char	*tmp;
	char	*c;
	int		in_sgl_quote;
	int		in_dbl_quote;

	in_sgl_quote = 0;
	in_dbl_quote = 0;
	*output = ft_strdup("");
	while (*str)
	{
		if (*str == SGL_QUOTE && !in_dbl_quote)
			in_sgl_quote = !in_sgl_quote;
		else if (*str == DBL_QUOTE && !in_sgl_quote)
			in_dbl_quote = !in_dbl_quote;
		else
		{
			c = ft_substr(str, 0, 1);
			tmp = ft_strjoin(*output, c);
			free(*output);
			free(c);
			*output = tmp;
		}
		str++;
	}
}
