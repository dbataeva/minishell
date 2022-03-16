/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:59:01 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:27:49 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *memptr1, const void *memptr2, size_t num)
{
	unsigned char	*mem1;
	unsigned char	*mem2;
	int				i;

	i = 0;
	mem1 = (unsigned char *)memptr1;
	mem2 = (unsigned char *)memptr2;
	while ((i < (int)num) && (mem1[i] == mem2[i]))
		i++;
	if (i == (int)num)
		return (0);
	else
		return (mem1[i] - mem2[i]);
}
