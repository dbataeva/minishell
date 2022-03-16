/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:53:47 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/09 20:58:11 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*array;
	unsigned char	ch;

	ch = (unsigned char)c;
	array = (unsigned char *)b;
	while (len)
	{
		array[len - 1] = ch;
		len--;
	}
	return (b);
}
