/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:38:48 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/13 20:46:52 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	len_dest = ft_strlen(dest);
	if (size < len_dest + 1)
		return (len_src + size);
	if (size > (len_dest + len_src))
		j = ft_strlcpy(&dest[len_dest], src, size);
	else
	{
		j = 0;
		while ((j + len_dest) < (size - 1))
		{
			dest[len_dest + j] = src[j];
			j++;
		}
		dest[len_dest + j] = '\0';
	}
	if (len_dest > size)
		return (len_src + size);
	return (len_src + len_dest);
}
