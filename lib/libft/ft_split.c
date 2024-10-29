/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:21:11 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/27 19:22:54 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c))
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
		if (s[i] == c)
			i++;
	}
	return (count);
}

static char	*word(char const *s, size_t i, char c)
{
	char	*word;
	size_t	word_size;
	size_t	j;
	size_t	cpyi;

	j = 0;
	cpyi = i;
	word_size = 0;
	while (s[cpyi] != c && s[cpyi])
	{
		word_size++;
		cpyi++;
	}
	word = malloc(sizeof(char) * (word_size + 1));
	if (!word)
		return (0);
	while (s[i] != c && s[i])
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

static char	**ft_free(char **tab, size_t word_count)
{
	size_t	i;

	i = 0;
	while (i < word_count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static char	**write_word(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && j < wordcount(s, c))
		{
			tab[j] = word(s, i, c);
			if (!tab[j])
				return (ft_free(tab, wordcount(s, c)));
			i = i + ft_strlen(tab[j]);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc((sizeof(char *)), (wordcount(s, c) + 1));
	if (!tab)
		return (NULL);
	write_word(s, c, tab);
	return (tab);
}
/*
int	main(void)
{
	char const	s[] = "Hello how are you";
	char **split = ft_split(s, ' ');
	int	i;

	i = 0;
	while (split[i])
		printf("ft_split returns %s \n", split[i++]);

	for (int i = 0; split[i]; i++) {
		free(split[i]);
	}
	free(split);
}*/
