/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:33:18 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 12:42:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	trim_tab(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		tab[i] = ft_strtrim(tab[i], "\"");
		if (tmp[0] == tab[i][0])
			tab[i] = ft_strtrim(tab[i], "\'");
		free(tmp);
		i++;
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

void	wait_childs(pid_t pid, int *exit_code)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else
		*exit_code = 1;
}
