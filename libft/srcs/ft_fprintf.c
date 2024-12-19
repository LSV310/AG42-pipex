/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:02:03 by agruet            #+#    #+#             */
/*   Updated: 2024/12/19 13:29:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_normal_chars(const char *s, int *current, int fd)
{
	int	start;
	int	len;

	start = *current;
	while (s[*current] && s[*current] != '%')
		(*current)++;
	len = *current - start;
	write(fd, &s[start], len);
	return (len);
}

static int	get_conversion(char c, va_list ap, int fd)
{
	if (c == 'c')
		return (ft_putchar_len_fd(va_arg(ap, int), fd));
	else if (c == 's')
		return (ft_putstr_len_fd(va_arg(ap, char *), fd));
	else if (c == 'p')
		return (ft_printptr_fd(va_arg(ap, unsigned long long), fd));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base_len_fd(va_arg(ap, int), BASE_10, 10, fd));
	else if (c == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_10, 10, fd));
	else if (c == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16L, 16, fd));
	else if (c == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16U, 16, fd));
	else if (c == '%')
		return (ft_putchar_len_fd('%', fd));
	else if (c == 0)
		return (0);
	else
		return (ft_putchar_len_fd('%', fd) + ft_putchar_len_fd(c, fd));
}

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	ap;
	int		len;
	int		current;

	if (!s)
		return (-1);
	va_start(ap, s);
	current = 0;
	len = 0;
	while (s[current])
	{
		if (s[current] == '%')
		{
			len += get_conversion(s[current + 1], ap, fd);
			if (s[current + 1])
				current += 2;
			else
				current += 1;
		}
		else
			len += print_normal_chars(s, &current, fd);
	}
	va_end(ap);
	return (len);
}
