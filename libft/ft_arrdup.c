/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:32:23 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 23:13:15 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (!new)
		return (0);
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
		{
			while (i >= 0)
				free(arr[i--]);
			return (0);
		}
		i++;
	}
	new[i] = 0;
	return (new);
}
