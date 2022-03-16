/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:34:31 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/11 12:13:04 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] == 32) || ((str[i] <= '\r') && (str[i] >= '\t'))) && str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	neg;

	k = 0;
	neg = 1;
	i = num(str);
	if (str[i] == '-')
	{
		neg = neg * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		k = k * 10 + str[i] - '0';
		i++;
	}
	return (k * neg);
}
