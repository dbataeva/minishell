/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:49:45 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/10 12:38:06 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

static void	ft_putstrn(char *str, int n, int fd)
{
	n = n - 1;
	while (n >= 0)
	{
		ft_putchar(*(str + n), fd);
		n--;
	}
	return ;
}

static void	ft_negnum(int nb, int fd)
{
	int		i;
	int		k;
	char	strneg[10];

	i = 0;
	k = 0;
	ft_putchar('-', fd);
	if (nb == -2147483648)
	{
		write(fd, "2147483648", 10);
		return ;
	}
	nb = nb * -1;
	while (nb > 0)
	{
		k = (nb % 10);
		strneg[i] = ('0' + k);
		nb = nb / 10;
		i++;
	}
	ft_putstrn(strneg, i, fd);
	return ;
}

void	ft_putnbr_fd(int nb, int fd)
{
	int		i;
	int		k;
	char	str[10];

	i = 0;
	k = 0;
	if (nb == 0)
		write(fd, "0", 1);
	else if (nb < 0)
		ft_negnum(nb, fd);
	else
	{
		while (nb > 0)
		{
			k = (nb % 10);
			str[i] = ('0' + k);
			nb = nb / 10;
			i++;
		}
		ft_putstrn(str, i, fd);
	}
	return ;
}
