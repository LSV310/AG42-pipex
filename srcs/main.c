/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/01/06 13:05:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	open_files(char *file1, char *file2, int *fd1, int *fd2)
{
	*fd1 = open(file1, O_RDONLY);
	if (*fd1 == -1)
	{
		perror("open");
		if (!access(file1, F_OK))
			exit(EXIT_FAILURE);
		*fd1 = 0;
	}
	// if (strcmp(file1, "here_doc"))
	// 	*fd2 = open(file2, O_WRONLY | O_CREAT, 0644);
	// else
	*fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd2 == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	free_cmd(char *cmd, char **args)
{
	int	i;

	i = 0;
	if (cmd)
		free(cmd);
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

void	exec_cmd(char *str, int *pipefd)
{
	char	*cmd;
	char	**args;
	char	*envp[1];
	pid_t	pid;

	args = ft_split(str, ' ');
	if (!args)
		exit(EXIT_FAILURE);
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
		execve(cmd, args, envp);
		perror("execve");
	}
	free_cmd(cmd, args);
	wait(NULL);
	return ;
}

int	main(int ac, char **av)
{
	int		pipefd[2];
	int		index;
	int		fd1;
	int		fd2;
	pid_t	pid;

	if (ac < 5)
		return (ft_putstr_fd("Error, arguments missing\n", 2), 1);
	open_files(av[1], av[ac - 1], &fd1, &fd2);
	pipe(pipefd);
	dup2(fd1, STDIN_FILENO);
	exec_cmd(av[2], pipefd);
	index = 3;
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
	(close(pipefd[0]), close(pipefd[1]));
	(close(fd1), close(fd2));
}
