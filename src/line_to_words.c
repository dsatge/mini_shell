/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/29 16:50:40 by dsatge           ###   ########.fr       */
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

int	ft_quotes(char *buffer, int i, t_quote quote)
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
	return (ft_putstr_fd("Error: unclosed quote\n", 2), -1);
}

int	is_word(char *buffer, int i, t_minish **mini_struct, int first_word)
{
    int len;
	int	start;
    t_quote quote;
    
    len = 0;
	start = i;
    quote = DEFAULT;
    while ((is_White_Space(buffer[i]) == false) && buffer[i])
    {
		if ((buffer[i] == '"' || buffer[i] == '\'' || buffer[i] == '|') && (len != 0))
			break;
		if ((buffer[i] == '|') && (len != 0))
			return (ft_tokenise(buffer, start, len, *mini_struct, first_word), len--);
		if (buffer[i] == '|' && len == 0)
			return (ft_tokenise(buffer, i, 1, *mini_struct, first_word), 1);
		if (buffer[i] == '"' || buffer[i] == '\''){
			len = ft_quotes(buffer, i, quote);
			if (len == -1)
				return (-1);
			ft_tokenise(buffer, i + 1, len - 1, *mini_struct, first_word);
			return (len + 1);
        }
        else
		    len++;
		i++;
    }
	ft_tokenise(buffer, start, len, *mini_struct, first_word);
    return (len);
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
