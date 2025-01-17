/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2025/01/17 09:58:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

pid_t	exec_cmd(char *str, int *pipefd, char **ep)
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
	if (access(cmd, F_OK | X_OK))
		return (free_cmd(cmd, args), ft_fprintf(2, "pipex: command not found\n"), 0);
	pid = fork();
	if (pid == -1)
		perror("fork fail");
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		execve(cmd, args, ep);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	free_cmd(cmd, args);
	return (pid);
}

int	main(int ac, char **av, char **ep)
{
	int		pipefd[2];
	int		fds[2];
	int		exit_code;
	int		i;

	if (ac < 5)
		return (ft_fprintf(2, "Error, arguments missing\n"));
	exit_code = 0;
	pipe(pipefd);
	i = open_files(ac, av, fds, pipefd);
	if (!parse_here_doc(av, NULL))
		exec_cmd(av[i++], pipefd, ep);
	while (i < ac - 1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
		pipe(pipefd);
		if (i == ac - 2)
			dup2(fds[1], pipefd[1]);
		wait_child(exec_cmd(av[i], pipefd, ep), &exit_code, i == ac - 2);
		i++;
	}
	close_fds(pipefd[0], pipefd[1], fds[0], fds[1]);
	return (exit_code);
}
