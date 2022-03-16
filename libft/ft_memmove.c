/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:38:47 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:18:37 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char		*dest;
	int					i;
	const unsigned char	*src;

	if (destination == source)
		return (destination);
	i = 0;
	src = (unsigned char *)source;
	dest = (unsigned char *)destination;
	if (dest < src)
	{
		while (i < (int)n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
		dest = ft_memcpy(dest, source, n);
	return (dest);
}
