/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:52:22 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/15 18:49:14 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = (char *)malloc(sizeof(char) * 1);
		sub[0] = '\0';
		return (sub);
	}
	if ((ft_strlen(s) - start) > len)
	{
		sub = (char *)malloc(sizeof(char) * len + 1);
		if (!sub)
			return (NULL);
	}
	else
		sub = (char *)malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, &s[start], len);
	sub[len] = '\0';
	return (sub);
}
