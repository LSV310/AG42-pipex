/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 12:23:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(char *str, int *pipefd, int *exit_code)
{
	char	*cmd;
	char	**args;
	char	*envp[1];
	pid_t	pid;

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
	wait_childs(pid, exit_code);
}

int	main(int ac, char **av)
{
	int		pipefd[2];
	int		index;
	int		fd1;
	int		fd2;
	int		exit_code;

	if (ac < 5)
		return (ft_putstr_fd("Error, arguments missing\n", 2), 1);
	index = open_files(ac, av, &fd1, &fd2);
	pipe(pipefd);
	dup2(fd1, STDIN_FILENO);
	exit_code = 0;
	exec_cmd(av[index++], pipefd, &exit_code);
	while (index < ac - 1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		pipe(pipefd);
		if (index == ac - 2)
			dup2(fd2, pipefd[1]);
		exec_cmd(av[index], pipefd, &exit_code);
		index++;
	}
	close_fds(pipefd[0], pipefd[1], fd1, fd2);
	return (exit_code);
}
