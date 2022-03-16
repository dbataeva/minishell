/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:15:52 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/18 12:00:22 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while ((big[i] != '\0') && (i < len) && (big[i] == little[j])
			&& (little[j] != '\0'))
		{
			i++;
			j++;
			if ((little[j] == '\0') && (i <= len))
				return ((char *)big + i - j);
		}
		if (big[i] != '\0')
			i = i + 1 - j;
	}
	return (NULL);
}
