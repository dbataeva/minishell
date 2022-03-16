/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:05:14 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/15 15:42:25 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		l_s1;
	int		l_s2;

	if (!s1 || !s2)
		return (NULL);
	l_s2 = ft_strlen(s2);
	l_s1 = ft_strlen(s1);
	join = (char *)malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (join)
	{
		join = ft_memcpy(join, s1, l_s1);
		ft_strlcpy(&join[l_s1], s2, (l_s1 + l_s2 + 1));
		return (join);
	}
	else
		return (NULL);
}
