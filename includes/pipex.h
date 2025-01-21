/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:21 by agruet            #+#    #+#             */
/*   Updated: 2025/01/21 16:35:51 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

int		open_files(int ac, char **av, int *fds, int *pipefd);
int		parse_here_doc(char **av, char **file1, int ac, int *pipefd);
char	**ft_parsed_split(char const *s, char c);
char	*parse_env(char **envp, char *cmd, char **args);
void	wait_child(pid_t pid, int *exit_code, int last);
void	free_cmd(char *cmd, char **args);
void	close_fds(int fd1, int fd2, int fd3, int fd4);

#endif
