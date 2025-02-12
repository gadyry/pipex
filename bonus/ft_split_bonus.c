/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:52:24 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/11 11:48:52 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;
	int		in_quotes;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	while (*s)
	{
		if (*s == '\'' && !in_quotes)
			in_quotes = 1;
		else if (*s == '\'' && in_quotes)
			in_quotes = 0;
		else if (*s != c && !in_word && !in_quotes)
		{
			in_word = 1;
			count++;
		}
		else if ((*s == c || *s == '\n') && !in_quotes)
			in_word = 0;
		s++;
	}
	return (count);
}

static size_t	calc_len(const char *s, char c)
{
	size_t	i;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	while (s[i] && (s[i] != c || in_quotes))
	{
		if (s[i] == '\'' && !in_quotes)
			in_quotes = 1;
		else if (s[i] == '\'' && in_quotes)
			in_quotes = 0;
		i++;
	}
	return (i);
}

static char	*fill_subs(const char **s, char c)
{
	size_t	len;
	char	*subs;
	size_t	i;
	int		in_quotes;

	while (**s == c && **s)
		(*s)++;
	len = calc_len(*s, c);
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	in_quotes = 0;
	while (i < len)
	{
		if (**s == '\'' && !in_quotes)
			in_quotes = 1;
		else if (**s == '\'' && in_quotes)
			in_quotes = 0;
		subs[i] = **s;
		i++;
		(*s)++;
	}
	subs[i] = '\0';
	return (subs);
}

static char	**free_2_dim(char **strs, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**strs;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < words)
	{
		strs[i] = fill_subs(&s, c);
		if (!strs[i])
			return (free_2_dim(strs, i));
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
