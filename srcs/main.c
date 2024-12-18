/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2024/12/18 17:42:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*gnl;

	if (ac < 2)
	{
		ft_printf("File name missing.\n");
		return (-1);
	}
	else if (ac > 2)
	{
		ft_printf("Too many arguments.\n");
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_printf("Cannot read file.\n");
	gnl = get_next_line(fd);
	ft_printf("%s", gnl);
	free(gnl);
	fd2 = dup(fd);
	gnl = get_next_line(fd2);
	ft_printf("%s", gnl);
	free(gnl);
	gnl = get_next_line(fd);
	ft_printf("%s", gnl);
	free(gnl);
}
