/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:12:12 by agruet            #+#    #+#             */
/*   Updated: 2025/01/24 14:24:00 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_here_doc(char **av, char **file1, int ac, int *pipefd)
{
	int	here_doc;
	int	len;

	len = ft_strlen(av[1]);
	if (len == 8 && ft_strncmp(av[1], "here_doc", len) == 0)
	{
		here_doc = 1;
		if (file1)
			*file1 = av[2];
		if (ac <= 5)
		{
			ft_fprintf(2, "Error, arguments missing\n");
			close_fds(pipefd[0], pipefd[1], -1, -1);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		here_doc = 0;
		if (file1)
			*file1 = av[1];
	}
	return (here_doc);
}

void	find_limiter(int fd, char *limiter, int *fd1)
{
	char	*gnl;
	size_t	len;

	if (!limiter)
		return ;
	*fd1 = -1;
	len = ft_strlen(limiter);
	ft_printf("> ");
	gnl = get_next_line(0);
	while (gnl)
	{
		if (ft_strlen(gnl) - 1 == len && ft_strncmp(gnl, limiter, len) == 0)
		{
			free(gnl);
			gnl = NULL;
			return ;
		}
		ft_fprintf(fd, gnl);
		free(gnl);
		ft_printf("> ");
		gnl = get_next_line(0);
	}
}

void	open_file1(int *fd1, char *file1, int *pipefd)
{
	*fd1 = open(file1, O_RDONLY);
	if (*fd1 == -1)
	{
		perror("input");
		*fd1 = open("/dev/null", O_RDONLY);
		if (*fd1 == -1)
		{
			close_fds(pipefd[0], pipefd[1], -1, -1);
			perror("input");
			exit(EXIT_FAILURE);
		}
	}
	dup2(*fd1, STDIN_FILENO);
}

void	open_file2(int *fds, char *file2, int here_doc, int *pipefd)
{
	if (here_doc)
		fds[1] = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fds[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
	{
		perror("output");
		if (fds[0] > 0)
			close(fds[0]);
		(close(pipefd[0]), close(pipefd[1]));
		exit(EXIT_FAILURE);
	}
}

int	open_files(int ac, char **av, int *fds, int *pipefd)
{
	int		here_doc;
	char	*file1;

	here_doc = parse_here_doc(av, &file1, ac, pipefd);
	if (!here_doc)
		open_file1(&fds[0], file1, pipefd);
	else
		find_limiter(pipefd[1], av[2], &fds[0]);
	open_file2(fds, av[ac - 1], here_doc, pipefd);
	if (!access(file1, F_OK) && access(file1, R_OK))
	{
		if (fds[0] > 0)
			close(fds[0]);
		if (fds[1] > 0)
			close(fds[1]);
		(close(pipefd[0]), close(pipefd[1]));
		exit(EXIT_FAILURE);
	}
	return (2 + here_doc);
}
