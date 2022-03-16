/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:34:48 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:26:25 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*array;
	int				i;

	i = 0;
	ch = (char)c;
	array = (unsigned char *)arr;
	while ((i < (int)n) && (array[i] != ch))
		i++;
	if (i < (int)n)
		return (array + i);
	else
		return (NULL);
}
