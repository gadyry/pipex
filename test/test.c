/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:41:03 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/29 11:32:01 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static size_t	calc_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*fill_subs(char const **s, char c)
{
	size_t	i;
	char	*subs;
	size_t	len;

	while (**s == c && **s)
		(*s)++;
	len = calc_len(*s, c);
	subs = (char *) malloc (sizeof (char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
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

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**strs;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
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
char	**get_path(char **envp)
{
	char	**paths;
	char	*path_value;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
		{
			path_value = envp[i] + 5;
			paths = ft_split(path_value, ':');
			free(path_value);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd, char **envp)
{
	char	**cmd_path;
	int		i;

	i = 0;
	cmd_path = get_path(envp);
	while (cmd_path[i])
	{
		if (!access(cmd_path[i], X_OK))
			return (cmd_path[i]);
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	char	**cmd = {"ls", "-all", NULL};
	char	*cmd_path = find_cmd_path(cmd, envp);
	printf("%s", cmd_path);
}