/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:13:20 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/10 11:13:54 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int arg)
{
	if (arg >= 'A' && arg <= 'Z')
		return (arg + 32);
	else
		return (arg);
}
