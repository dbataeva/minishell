/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:33:53 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 11:37:39 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i])
		&& ((unsigned char)s1[i] != '\0') && (i < (int)n))
		i++;
	if (i == (int)n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
