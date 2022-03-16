/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:28:11 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/11 14:31:05 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	int		i;

	if (!s || !f)
		return (NULL);
	mapi = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapi)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		mapi[i] = s[i];
		i++;
	}
	mapi[i] = '\0';
	i = 0;
	while (mapi[i] != '\0')
	{
		mapi[i] = f(i, mapi[i]);
		i++;
	}
	return (mapi);
}
