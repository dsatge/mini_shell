/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/14 17:46:09 by dsatge           ###   ########.fr       */
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
    if (buffer[i] == '"')
        quote = DOUBLE_QUOTE;
    if (buffer[i] == '\'')
        quote = SINGLE_QUOTE;
	i++;
	while (buffer[i])
	{
		if (buffer[i] == '"' && quote == DOUBLE_QUOTE)
			return(len + 1);
		if (buffer[i] == '\'' && quote == SINGLE_QUOTE)
			return(len + 1);		
        i++;
		len++;
	}
	return (ft_putstr_fd("Error: unclosed quote\n", 2), EXIT_FAILURE);
}

int	ft_count_word(char *buffer)
{
	int i;
	// int len = 0;
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
				quote = ft_quotes(buffer, i, quote);
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
    while ((is_White_Space(buffer[i]) == false) && buffer[i])
    {
        if (buffer[i] == '"' || buffer[i] == '\'')
        {
            len = ft_quotes(buffer, i, quote);
			return (len + 1);
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
	while (buffer[i])
	{
        i += is_word(buffer, i);
		printf("end of word = %i last char = %c\n", i, buffer[i]);
        while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
    }
    return ;
}