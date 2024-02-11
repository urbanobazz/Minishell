/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_skip_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:08:13 by lodemetz          #+#    #+#             */
/*   Updated: 2024/02/11 16:45:41 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_words_quotes(char const *s, char c)
{
	unsigned int	nwords;
	int				sq;
	int				dq;

	sq = 0;
	dq = 0;
	nwords = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			nwords++;
		while (*s && (*s != c || sq || dq))
		{
			if (*s == SGL_QUOTE && !dq)
				sq = !sq;
			else if (*s == DBL_QUOTE && !sq)
				dq = !dq;
			s++;
		}
	}
	return (nwords);
}

unsigned int	get_length_quotes(char const *s, char c)
{
	unsigned int	i;
	int				sq;
	int				dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i] && (s[i] != c || sq || dq))
	{
		if (s[i] == SGL_QUOTE && !dq)
			sq = !sq;
		else if (s[i] == DBL_QUOTE && !sq)
			dq = !dq;
		i++;
	}
	return (i);
}

char	**split_skip_quotes(char const *s, char c)
{
	unsigned int	nwords;
	char			**arr;
	unsigned int	i;
	int				len;

	nwords = count_words_quotes(s, c);
	arr = malloc((nwords + 1) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	while (i < nwords)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			len = get_length_quotes(s, c);
			arr[i] = ft_substr(s, 0, len);
			s += len;
		}
		i++;
	}
	arr[i] = 0;
	return (arr);
}
