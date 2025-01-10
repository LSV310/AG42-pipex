/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 17:28:18 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(char *str, int *pipefd, int *exit_code, char **ep)
{
	char	*cmd;
	char	**args;
	pid_t	pid;

	args = ft_parsed_split(str, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	cmd = ft_strjoin("/bin/", args[0]);
	if (!cmd)
		(free_cmd(NULL, args), exit(EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("fork error", 2);
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(cmd, args, ep) == -1)
			(perror("execve"), exit(EXIT_FAILURE));
	}
	free_cmd(cmd, args);
	wait_child(pid, exit_code);
}

int	main(int ac, char **av, char **ep)
{
	int		pipefd[2];
	int		index;
	int		fd1;
	int		fd2;
	int		exit_code;

	if (ac < 5)
		return (ft_putstr_fd("Error, arguments missing\n", 2), 1);
	exit_code = 0;
	pipe(pipefd);
	index = open_files(ac, av, &fd1, &fd2, pipefd);
	if (!parse_here_doc(av, NULL))
		exec_cmd(av[index++], pipefd, &exit_code, ep);
	while (index < ac - 1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		pipe(pipefd);
		if (index == ac - 2)
			dup2(fd2, pipefd[1]);
		exec_cmd(av[index], pipefd, &exit_code, ep);
		index++;
	}
	close_fds(pipefd[0], pipefd[1], fd1, fd2);
	return (exit_code);
}
