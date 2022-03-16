/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:57:40 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/11 14:27:00 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_swap(char *a, char *b)
{
	char	change;

	change = *a;
	*a = *b;
	*b = change;
	return ;
}

static void	*ft_putnbr(int nb, char *dest, int size)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (nb < 0)
	{
		dest[size - 2] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		k = (nb % 10);
		dest[i] = ('0' + k);
		nb = nb / 10;
		i++;
	}
	dest[size - 1] = '\0';
	return (dest);
}

static int	ft_numlen(int nb)
{
	int	len;
	int	copy;

	copy = nb;
	len = 1;
	if (nb < 0)
	{
		len++;
		copy = copy * -1;
	}
	while (copy > 0)
	{
		copy = copy / 10;
		len++;
	}
	return (len);
}

static char	*f_malloc(int size, int nb)
{
	char	*dest;
	int		i;
	int		j;

	dest = (char *)malloc(sizeof(char) * size);
	if (dest)
	{
		if (nb == -2147483648)
			dest = ft_memcpy(dest, "-2147483648\0", size);
		else if (nb == 0)
			dest = ft_memcpy(dest, "0\0", size);
		else
		{
			dest = ft_putnbr(nb, dest, size);
			i = 0;
			j = size - 2;
			while (i < (size / 2))
				f_swap(&dest[i++], &dest[j--]);
		}
		return (dest);
	}
	else
		return (NULL);
}

char	*ft_itoa(int nb)
{
	int		size;
	char	*str;

	if (nb == -2147483648)
		str = f_malloc(12, nb);
	else if (nb == 0)
		str = f_malloc(2, nb);
	else
	{
		size = ft_numlen(nb);
		str = f_malloc(size, nb);
	}
	return (str);
}
