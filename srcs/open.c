/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:12:12 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 12:18:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_here_doc(char **av, char **file1)
{
	int	here_doc;

	if (strcmp(av[1], "here_doc") == 0)
	{
		here_doc = 1;
		if (file1)
			*file1 = av[2];
	}
	else
	{
		here_doc = 0;
		if (file1)
			*file1 = av[1];
	}
	return (here_doc);
}

void	open_file1(int *fd1, char *file1)
{
	*fd1 = open(file1, O_RDONLY);
	if (*fd1 == -1)
	{
		perror("open");
		*fd1 = open("/dev/null", O_RDONLY);
		if (*fd1 == -1)
			(perror("open"), exit(EXIT_FAILURE));
	}
}

void	open_file2(int *fd2, char *file2, int fd1, int here_doc)
{
	if (here_doc)
		*fd2 = open(file2, O_WRONLY | O_CREAT, 0644);
	else
		*fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd2 == -1)
	{
		perror("open");
		if (fd1 > 0)
			close(fd1);
		exit(EXIT_FAILURE);
	}
}

int	open_files(int ac, char **av, int *fd1, int *fd2)
{
	int		here_doc;
	char	*file1;

	here_doc = parse_here_doc(av, &file1);
	open_file1(fd1, file1);
	open_file2(fd2, av[ac - 1], *fd1, here_doc);
	if (!access(file1, F_OK) && access(file1, R_OK))
	{
		if (*fd1 > 0)
			close(*fd1);
		if (*fd2 > 0)
			close(*fd2);
		exit(EXIT_FAILURE);
	}
	return (2 + here_doc);
}
