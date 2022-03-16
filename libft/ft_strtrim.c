/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:20:17 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/11 14:33:38 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bingo(char const s1, char const *set)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			k++;
		i++;
	}
	if (k)
		return (1);
	else
		return (0);
}

static int	is_tes(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = ft_strlen(s1) - 1;
	k = 0;
	while ((i >= 0) && (bingo(s1[i], set)))
	{
		k++;
		i--;
	}
	return (k);
}

static int	is_set(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while ((s1[i] != '\0') && bingo(s1[i], set))
	{
		k++;
		i++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		j;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = is_set(s1, set);
	if (i == (int)ft_strlen(s1))
	{
		trim = (char *)malloc(sizeof(char) * 1);
		if (!trim)
			return (NULL);
		trim[0] = '\0';
		return (trim);
	}
	j = is_tes(s1, set);
	len = ft_strlen(s1) - i - j;
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (NULL);
	trim = ft_memcpy(trim, &s1[i], len);
	trim[len] = '\0';
	return (trim);
}
