/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by agruet            #+#    #+#             */
/*   Updated: 2024/12/31 17:11:06 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmd(char *cmd, char **args)
{
	int	i;

	i = 0;
	while (args[i])
			free(args[i++]);
	free(args);
	free(cmd);
}

void	exec_cmd(char *str, pid_t *pid, int *pipefd)
{
	char	*cmd;
	char	**args;
	char	*envp[1] = {NULL};

	args = ft_split(str, ' ');
	cmd = ft_strjoin("/bin/", args[0]);

	*pid = fork();
	if (*pid == -1)
		ft_putstr_fd("fork error", 2);
	else if (*pid == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve(cmd, args, envp);
		ft_printf("ERROR\n");
	}
	free_cmd(cmd, args);
	return ;
}

int	main(int ac, char **av)
{
	int		pipefd[2];
	int		fd1;
	int		fd2;
	pid_t	pid;

	pipe(pipefd);
	if (ac < 5)
		return (ft_putstr_fd("Error, arguments missing\n", 2), 1);

	fd1 = open(av[1], O_RDWR);
	if (fd1 == -1)
		ft_printf("No such file or directory.\n");
	fd2 = open(av[4], O_RDWR);

	dup2(fd1, pipefd[0]);
	close(fd1);
	exec_cmd(av[2], &pid, pipefd);
	wait(NULL);
	dup2(pipefd[0], pipefd[1]);
	dup2(fd2, pipefd[1]);
	close(fd2);
	exec_cmd(av[3], &pid, pipefd);
	wait(NULL);
	close(pipefd[0]);
	close(pipefd[1]);
}
