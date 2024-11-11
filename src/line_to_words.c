/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/11 04:25:09 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
	{
		return (0);
	}
	return (1);
}

int	ft_quotes(char *buffer, int i, char quote_type)
{
	int len;

	len = 1;
	i++;
	while (buffer[i])
	{
		if (buffer[i] == quote_type)
			return(len - 1);
		i++;
		len++;
	}
	return (0);
}

int	ft_count_word(char *buffer)
{
	int i;
	int len = 0;
	int word;

	word = 0;
	i = 0;
	while (!(ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
		i++;
	while (buffer[i] != '\0')
	{
		while ((ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
		{
			if (buffer[i] == '"' || buffer[i] == 39)
			{
				len = ft_quotes(buffer, i, buffer[i]);
				i = i + len;
			}
			i++;
		}
		while (!(ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
			i++;
		word++;
	}
	return (word);
}

int word_len(char *buffer, int i)
{
    int len;

    len = 0;
    while ((ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
    {
        if (buffer[i] == '"' || buffer[i] == 39)
        {
            len = ft_quotes(buffer, i, buffer[i]);
            i = i + len;
        }
        i++;
    }
    return (i);
}

char *ft_isword(char *buffer, int start, int end)
{
    int     i;
    char    *word;

    i = 0;
    if (buffer[start] == '"' || buffer[start] == 39)
    {
        start = start + 1;
        end = end - 1;
    }
    word = malloc(sizeof(char) * (end - start + 1));
    if (!word)
        return (ft_putstr_fd("Error: malloc failure ft_isword\n", 2), NULL);
    while (start < end)
    {
        word[i] = buffer[start];
        i++;
        start++;
    }
    word[i] = '\0';
    printf("word = %s\n", word);
    return (word);
}

char **ft_split_word(char *buffer)
{
    char    **tab;
	int i;
    int j;
    int line;

    tab = malloc(sizeof(char *) * (ft_count_word(buffer) + 1)); // leaks from here !!!!
    if (!tab)
        return (ft_putstr_fd("Error: malloc failur ft_split_word\n", 2), NULL);
    i = 0;
    j = 0;
    line = 0;
	while (!(ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
		i++;
	while (buffer[i] != '\0')
	{
		j = i;
        i = word_len(buffer, i);
        tab[line] = ft_isword(buffer, j, i);
        printf("tab[%i] = %s\n", line, tab[line]);
        if (!tab)
            return (ft_putstr_fd("Error: malloc failur ft_split_word", 2), NULL);
        line++;
        while (!(ft_iswhitespace(buffer[i])) && buffer[i] != '\0')
			i++;
    }
    tab[line] = 0;
    return (tab);
}
