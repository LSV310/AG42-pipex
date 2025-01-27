/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:22:20 by agruet            #+#    #+#             */
/*   Updated: 2025/01/27 13:28:59 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*new_cmd(char *old_cmd, char **args)
{
	char	*new_cmd;

	if (!old_cmd)
		return (NULL);
	new_cmd = ft_strjoin("/", old_cmd);
	if (!new_cmd)
		(free_cmd(NULL, args), exit(EXIT_FAILURE));
	return (new_cmd);
}

static char	*find_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
			return (path + 5);
		i++;
	}
	return (NULL);
}

static char	*try_path(char *cmd, char **path, int i, char **args)
{
	char	*join;

	if (!cmd)
		return (NULL);
	join = ft_strjoin(path[i], cmd);
	if (!join)
		(free_cmd(cmd, args), free_cmd(NULL, path), exit(EXIT_FAILURE));
	if (!access(join, X_OK))
		return (join);
	free(join);
	return (NULL);
}

char	*parse_env(char **envp, char *cmd, char **args)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	cmd = new_cmd(cmd, args);
	temp = find_path(envp);
	if (!temp)
		return (free(cmd), NULL);
	path = ft_split(temp, ':');
	if (!path)
		(free_cmd(cmd, args), exit(EXIT_FAILURE));
	temp = NULL;
	while (path[i])
	{
		temp = try_path(cmd, path, i, args);
		if (temp)
			break ;
		i++;
	}
	free_cmd(cmd, path);
	return (temp);
}
