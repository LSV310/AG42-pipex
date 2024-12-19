/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:11:29 by agruet            #+#    #+#             */
/*   Updated: 2024/12/19 13:29:54 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_len_fd(int c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_putstr_len_fd(char	*s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

int	ft_putnbr_base_fd(unsigned int n, char *base, int base_len, int fd)
{
	static int	result;

	result = 0;
	if (n >= (unsigned int)base_len)
		ft_putnbr_base_fd(n / base_len, base, base_len, fd);
	n = base[n % (unsigned int)base_len];
	write(fd, &n, 1);
	result++;
	return (result);
}

int	ft_putnbr_base_len_fd(int n, char *base, int base_len, int fd)
{
	unsigned int	nb;
	unsigned int	is_neg;

	is_neg = 0;
	if (n < 0)
	{
		nb = -n;
		write(fd, "-", 1);
		is_neg = 1;
	}
	else
		nb = n;
	return (ft_putnbr_base_fd(nb, base, base_len, fd) + is_neg);
}

int	ft_printptr_fd(unsigned long long ptr, int fd)
{
	char	*base;
	char	buff[17];
	int		i;
	int		result;

	if (!ptr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	base = BASE_16L;
	i = 0;
	while (ptr > 0)
	{
		buff[i] = base[ptr % 16];
		i++;
		ptr /= 16;
	}
	result = i;
	write(fd, "0x", 2);
	while (--i >= 0)
		write(fd, &buff[i], 1);
	return (result + 2);
}
