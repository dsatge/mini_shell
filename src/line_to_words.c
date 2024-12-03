/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/03 18:36:15 by dsatge           ###   ########.fr       */
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

int	ft_quotes(char *buffer, int i)
{
	int len;
	t_quote	quote;

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
	return (ft_putstr_fd("Error: unclosed quote\n", 2), -1);
}

int	is_word(char *buffer, int i, t_minish **mini_struct, int first_word)
{
    int 	len;
	int		start;
	char	*tmp;
	char	*tmp_quote;
	char	*word;
    
    len = 0;
	word = NULL;
	start = i;
    while ((is_White_Space(buffer[i]) == false) && buffer[i] != '|' && buffer[i])
    {
		if ((buffer[i] == '"' || buffer[i] == '\'')){
			printf("pos of i = %i\n", i);
			if (word)
				tmp = word;
			else
			{
				tmp = word_from_str(buffer, start, len);
				len += ft_quotes(buffer, start + len);
				if (len == -1)
					return (free(tmp), -1);
			}
			tmp_quote = word_from_str(buffer, i + 1, len);
			word = ft_strjoin(tmp, tmp_quote);
			free(tmp);
			free(tmp_quote);
			if (buffer[i + len + 1] || is_White_Space(buffer[i + 1]) == false || buffer[i + 1] != '|')
				start = i + len + 1;
			else
				start = -1;
			printf("start = %i len = %i\n", start, len);
        }
        else
		    len++;
		i++;
    }
	if (start != -1 && buffer[i] != '|')
	{
		if (word)
		{
			tmp = word;
			tmp_quote = word_from_str(buffer, start, len);
			len += ft_strlen(tmp_quote);
			word = ft_strjoin(tmp, tmp_quote);
			free(tmp);
			free(tmp_quote);
		}
		else
		{
			word = word_from_str(buffer, start, len);
			len += ft_strlen(word);
		}
	}
	if (buffer[i] == '|' && len != 0)
			return (ft_tokenise_word(word, *mini_struct, first_word), len--);
	if (buffer[i] == '|' && len == 0)
			return (ft_tokenise_word(ft_strdup("|"), *mini_struct, first_word), 1);
    return (ft_tokenise_word(word, *mini_struct, first_word), len);
}

t_token	*ft_split_word(char *buffer, t_minish *mini_struct)
{
	int i;
	int	word;
	int	first_word;
	t_token	*head;

    i = 0;
	word = 0;
	first_word = 0;
	mini_struct->element = malloc(sizeof(t_token));
	if (!mini_struct)
		return (NULL);
	mini_struct->element->str = NULL;
	head = mini_struct->element;
	while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
	while (buffer[i]){
		word = is_word(buffer, i, &mini_struct, first_word);
		if (word == -1)
			return (head);
		i += word;
		first_word++;
        while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
    }
    return (head);
}
