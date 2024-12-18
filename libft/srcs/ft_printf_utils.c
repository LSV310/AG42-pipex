/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:51 by agruet            #+#    #+#             */
/*   Updated: 2024/12/17 15:10:58 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_len(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr_len(char	*s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_putnbr_base(unsigned int n, char *base, unsigned int base_len)
{
	static int	result;

	result = 0;
	if (n >= base_len)
		ft_putnbr_base(n / base_len, base, base_len);
	n = base[n % base_len];
	write(1, &n, 1);
	result++;
	return (result);
}

int	ft_putnbr_base_len(int n, char *base, int base_len)
{
	unsigned int	nb;
	unsigned int	is_neg;

	is_neg = 0;
	if (n < 0)
	{
		nb = -n;
		write(1, "-", 1);
		is_neg = 1;
	}
	else
		nb = n;
	return (ft_putnbr_base(nb, base, base_len) + is_neg);
}

int	ft_printptr(unsigned long long ptr)
{
	char	*base;
	char	buff[17];
	int		i;
	int		result;

	if (!ptr)
	{
		write(1, "(nil)", 5);
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
	write(1, "0x", 2);
	while (--i >= 0)
		write(1, &buff[i], 1);
	return (result + 2);
}
