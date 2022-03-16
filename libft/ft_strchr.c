/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:54:11 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:40:01 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	character;
	int				i;

	i = 0;
	character = (unsigned char)ch;
	while (str[i] != '\0')
	{
		if (str[i] == character)
			return ((char *)str + i);
		else
			i++;
	}
	if (character == '\0')
		return ((char *)str + ft_strlen(str));
	return (NULL);
}
