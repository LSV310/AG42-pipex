/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:18 by agruet            #+#    #+#             */
/*   Updated: 2025/01/27 14:31:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (fd4 >= 0)
		close(fd4);
}

void	wait_child(pid_t pid, int *exit_code, int last)
{
	int	status;

	if (pid == 0)
	{
		*exit_code = 127;
		ft_fprintf(2, "pipex: command not found\n");
		return ;
	}
	if (!last)
		waitpid(pid, &status, WNOHANG);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = 128 + WTERMSIG(status);
	else
		*exit_code = 1;
}
