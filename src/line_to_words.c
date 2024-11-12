/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/12 20:32:49 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_White_Space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
	{
		return (true);
	}
	return (false);
}

int	ft_quotes(char *buffer, int i, enum e_quote_status quote)
{
	int len;

	len = 0;
	i++;
    if (buffer[i] == '"')
        quote = DOUBLE_QUOTE;
    if (buffer[i] == '\'')
        quote = SINGLE_QUOTE;
    i++;
	while (buffer[i])
	{
		if (buffer[i] == '"' && quote == DOUBLE_QUOTE)
			return(quote = DEFAULT, len);
		if (buffer[i] == '\'' && quote == SINGLE_QUOTE)
			return(quote = DEFAULT, len);		
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
    enum e_quote_status  quote;

	word = 0;
	i = 0;
	while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
    quote = DEFAULT;
	while (buffer[i] != '\0')
	{
		while ((is_White_Space(buffer[i]) == false) && buffer[i] != '\0')
		{
			if (quote == DEFAULT && (buffer[i] == '"' || buffer[i] == 39))
			{
				quote = ft_quotes(buffer[i], quote);
			}
			i++;
		}
		while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
		word++;
	}
	return (word);
}


// char *ft_isword(char *buffer, int start, int end)
// {
//     int     i;
//     char    *word;

//     i = 0;
//     if (buffer[start] == '"' || buffer[start] == '\'')
//     {
//         start = start + 1;
//         printf("start = %i\n", start);
//         end = end - 1;
//         printf("end = %i\n", end);
//     }
//     word = malloc(sizeof(char) * (end - start) + 1);
//     if (!word)
//         return (ft_putstr_fd("Error: malloc failure ft_isword\n", 2), NULL);
//     while (start < end)
//     {
//         word[i] = buffer[start];
//         i++;
//         start++;
//     }
//     word[i] = '\0';
//     printf("word = %s\n", word);
//     return (word);
// }

int is_word(char *buffer, int i)
{
    int len;
    enum e_quote_status quote;
    

    len = 0;
    quote = DEFAULT;
    while ((is_White_Space(buffer[i]) == false) && buffer[i] != '\0')
    {
        if ((buffer[i] == '"' || buffer[i] == '\'') && quote ==  DEFAULT)
        {
            len = ft_quotes(buffer, i, quote);
            if (quote != DEFAULT)
                return (ft_putstr_fd("Error: unclosed quote\n", 2), -1);
            i = i + len;
        }
        else
            len++;
        i++;
    }
    return (len);
}

void ft_split_word(char *buffer)
{
	int i;

    i = 0;
	while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
	while (buffer[i] != '\0')
	{
		// j = i;
        // i = word_len(buffer, i);
        // tab[line] = ft_isword(buffer, j, i);
        i = is_word(buffer, i);
        // printf("tab[%i] = %s\n", line, tab[line]);
        while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
    }
    return ;
}