/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:30:59 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 10:41:06 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	unsigned char	symb;
	int				i;
	int				j;

	i = 0;
	j = -1;
	symb = symbol;
	while (string[i] != '\0')
	{
		if (string[i] == symb)
			j = i;
		i++;
	}
	if (j != -1)
		return ((char *)string + j);
	else if (symb == '\0')
		return ((char *)string + ft_strlen(string));
	else
		return (NULL);
}
