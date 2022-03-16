/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:46:34 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/14 12:13:08 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		l;
	char	*dup;

	l = ft_strlen(str) + 1;
	dup = (char *)malloc(sizeof(char) * l);
	if (dup)
	{
		ft_strlcpy(dup, str, l);
		return (dup);
	}
	else
		return (NULL);
}
