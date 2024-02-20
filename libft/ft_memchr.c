/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:52:45 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/13 13:19:53 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void *ft_memchr(const void *s, int c, size_t n)
{
	size_t i;
	unsigned char *uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (uc_s[i] == (unsigned char)c)
			return (void *)(&uc_s[i]);
		i++;
	}
	return 0;
}

