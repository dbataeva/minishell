/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:34:19 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/09 18:25:07 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;

	if (dest == src)
		return (dest);
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (n)
	{
		destination[n - 1] = source[n - 1];
		n--;
	}
	return (dest);
}
