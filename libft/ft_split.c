/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:55:20 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/15 17:58:30 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		if (s[i] != c)
		{
			while ((s[i] != c) && (s[i] != '\0'))
			{
				i++;
				j++;
			}
			return (j);
		}
	}
	return (j);
}

static int	entrance(char const *s, char c, int a)
{
	int	i;

	i = 0;
	if (a == 1)
	{
		while ((s[i] != '\0') && (s[i] == c))
			i++;
		if ((s[i] != c) && (s[i] != '\0'))
			return (i);
	}
	if (a == 2)
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		if (s[i] != '\0')
			return (i);
	}
	return (-1);
}

static int	num_words(char const *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		if ((s[i] != c) && (s[i] != '\0') && (i == 0))
			num++;
		if ((s[i] != c) && (s[i] != '\0') && (i != 0))
			num++;
		while ((s[i] != c) && (s[i] != '\0'))
			i++;
	}
	return (num);
}

static int	ft_cut(char **split, char const *s, char c, int num_wrds)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = entrance(&s[0], c, 1);
	len = 0;
	while (i < num_wrds)
	{
		len = length(&s[j], c);
		if (!len)
			return (-1);
		split[i] = ft_substr(s, j, len);
		if (!split[i])
			return (i);
		i++;
		j = entrance(&s[j], c, 1) + len + entrance(&s[j + len], c, 2) + j;
	}
	split[num_wrds] = NULL;
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		num_wrds;

	if (!s)
	{
		split = (char **)malloc(sizeof(char *) * 1);
		split[0] = NULL;
		return (split);
	}
	num_wrds = num_words(s, c);
	split = (char **)malloc(sizeof(char *) * (num_wrds + 1));
	if (!split)
		return (NULL);
	i = ft_cut(split, s, c, num_wrds);
	if (i != -1)
	{
		i = i + 1;
		while (i--)
			free(split[i]);
		free(split);
		return (NULL);
	}
	return (split);
}
