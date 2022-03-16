/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:46:13 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:24:18 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		sym;
	int					i;

	i = 0;
	sym = (unsigned char)c;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < (int)n)
	{
		d[i] = s[i];
		if (s[i] == sym)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
