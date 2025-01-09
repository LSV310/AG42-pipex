/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/01/09 16:51:08 by agruet           ###   ########.fr       */
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

int	open_files(int ac, char **av, int *fd1, int *fd2)
{
	int		here_doc;
	char	*file1;

	here_doc = parse_here_doc(av, &file1);
	*fd1 = open(file1, O_RDONLY);
	if (*fd1 == -1)
	{
		perror("open");
		*fd1 = 0;
	}
	if (here_doc)
		*fd2 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	else
		*fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd2 == -1)
	{
		perror("open");
		if (*fd1 > 0)
			close(*fd1);
		exit(EXIT_FAILURE);
	}
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

void	exec_cmd(char *str, int *pipefd)
{
	char	*cmd;
	char	**args;
	char	*envp[1];
	pid_t	pid;
	int		status;

	args = ft_parsed_split(str, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	trim_args(args);
	cmd = ft_strjoin("/bin/", args[0]);
	if (!cmd)
		(free_cmd(NULL, args), exit(EXIT_FAILURE));
	envp[0] = NULL;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("fork error", 2);
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(cmd, args, envp) == -1)
			(perror("execve"), exit(EXIT_FAILURE));
	}
	free_cmd(cmd, args);
	waitpid(pid, &status, 0);
	if (status)
		exit(EXIT_FAILURE);
	return ;
}

int	main(int ac, char **av)
{
	int		pipefd[2];
	int		index;
	int		fd1;
	int		fd2;
	pid_t	pid;

	char	*tab[6] = {"a.out", "infile.txt", "sed \"s/And/But/\"", "awk \"{count++} END {printf \\\"count: %i\\\" , count}\"", "outfile.txt"};
	av = tab;
	if (ac < 5)
		return (ft_putstr_fd("Error, arguments missing\n", 2), 1);
	index = open_files(ac, av, &fd1, &fd2);
	pipe(pipefd);
	dup2(fd1, STDIN_FILENO);
	exec_cmd(av[index++], pipefd);
	while (index < ac - 1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		pipe(pipefd);
		if (index == ac - 2)
			dup2(fd2, pipefd[1]);
		exec_cmd(av[index], pipefd);
		index++;
	}
	close_fds(pipefd[0], pipefd[1], fd1, fd2);
}
