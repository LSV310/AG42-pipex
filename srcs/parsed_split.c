/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:03 by agruet            #+#    #+#             */
/*   Updated: 2025/01/10 12:42:41 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	find_word(const char *s, char c, int *start, int *end)
{
	while (s[*end] && s[*end] == c)
		(*end)++;
	*start = *end;
	while (s[*end] && s[*end] != c)
	{
		if (s[*end] == '\'')
		{
			(*end)++;
			while (s[*end] && s[*end] != '\'')
				(*end)++;
		}
		if (s[*end] == '\"')
		{
			(*end)++;
			while (s[*end] && s[*end] != '\"')
				(*end)++;
		}
		else
			(*end)++;
	}
}

static void	skip_quotes(char const *str)
{
	if (*str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
	}
	else if (*str == '\"')
	{
		str++;
		while (*str && *str != '\"')
			str++;
	}
	else
		str++;
}

static int	count_word(char const *str, char c)
{
	int	in_word;
	int	number;

	in_word = 0;
	number = 0;
	while (*str)
	{
		if (*str && *str != c && in_word == 0)
		{
			in_word = 1;
			number++;
		}
		else if (*str == c)
			in_word = 0;
		skip_quotes(str);
	}
	return (number);
}

char	**ft_parsed_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		i;
	int		start;
	int		end;

	words = count_word(s, c);
	tab = ft_calloc(words + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = 0;
	end = 0;
	while (s[end] && i < words)
	{
		find_word(s, c, &start, &end);
		tab[i] = ft_calloc(end - start + 1, sizeof(char));
		if (!tab[i])
			return (free_tab(tab, i));
		ft_strlcpy(tab[i++], s + start, end - start + 1);
	}
	trim_tab(tab);
	return (tab);
}
