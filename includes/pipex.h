/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:21 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 12:42:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

int		open_files(int ac, char **av, int *fd1, int *fd2);
char	**ft_parsed_split(char const *s, char c);
void	trim_tab(char **tab);
void	wait_childs(pid_t pid, int *exit_code);
void	free_cmd(char *cmd, char **args);
void	close_fds(int fd1, int fd2, int fd3, int fd4);

#endif
