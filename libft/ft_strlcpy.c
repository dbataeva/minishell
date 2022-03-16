/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:42:32 by cchromos          #+#    #+#             */
/*   Updated: 2020/12/04 13:01:14 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	if (!src)
		return (0);
	if (!size || !dest)
		return (len = ft_strlen(src));
	len = ft_strlen(src);
	if (len < size)
	{
		i = -1;
		while (++i <= len)
			dest[i] = src[i];
	}
	else
	{
		i = -1;
		while (++i < size - 1)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	return (len);
}
