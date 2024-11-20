/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/20 20:07:19 by dsatge           ###   ########.fr       */
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

int is_word(char *buffer, int i, t_token *element, int first_word)
{
    int len;
	int	start;
    enum e_quote_status quote;
    
    len = 0;
    quote = DEFAULT;
	start = i;
    while ((is_White_Space(buffer[i]) == false) && buffer[i])
    {
        if (buffer[i] == '"' || buffer[i] == '\'')
        {
            len = ft_quotes(buffer, i, quote);
			ft_tokenise(buffer, i, len, element, first_word);
			return (len + 1);
        }
        else
		    len++;
		i++;
    }
	ft_tokenise(buffer, start, len, element, first_word);
    return (len);
}

void	ft_split_word(char *buffer, t_token *element)
{
	int i;
	int	first_word;
	t_token	*head;

    i = 0;
	first_word = 0;
	head = element;
	while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
	while (buffer[i])
	{
        i += is_word(buffer, i, element, first_word);
		first_word++;
        while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
    }
	ft_print_list(head);
    return ;
}