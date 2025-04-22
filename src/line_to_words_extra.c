/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:37:04 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 02:00:50 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_quotes(char *buffer, t_minish *minish, char *tmp)
{
	char	*quote_word;
	char	*joined_words;

	joined_words = NULL;
	quote_word = ft_quotes(buffer, minish);
	if (!quote_word)
		return (NULL);
	if (tmp)
	{
		joined_words = ft_strjoin(tmp, quote_word);
		if (!joined_words)
			return (ft_putstr_fd("Error ft_strjoin: ft_join_quotes\n", 2),
				NULL);
		return (free(quote_word), free(tmp), joined_words);
	}
	return (quote_word);
}

int	ft_split_word(char *buffer, t_minish *mini_struct)
{
	t_token	*head;

	mini_struct->i = 0;
	mini_struct->count_word = 0;
	mini_struct->pipex->nbr_cmds = 1;
	mini_struct->element = ft_calloc(sizeof(t_token), 1);
	if (!mini_struct->element)
		return (EXIT_FAILURE);
	head = mini_struct->element;
	if (skip_initial_whitespace(buffer, mini_struct) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_words(buffer, mini_struct) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (head)
		mini_struct->head_token = head;
	return (EXIT_SUCCESS);
}

char	*ft_quotes(char *buffer, t_minish *minish)
{
	int		len;
	int		start;
	char	*word;
	t_quote	quote;

	len = 0;
	quote = get_quote_type(buffer[minish->i]);
	start = minish->i;
	minish->i++;
	while (buffer[minish->i])
	{
		if (buffer[minish->i] == '"' && quote == DOUBLE_QUOTE)
		{
			word = word_from_str(buffer, start + 1, start + len + 1);
			return (word);
		}
		if (buffer[minish->i] == '\'' && quote == SINGLE_QUOTE)
		{
			word = word_from_str(buffer, start + 1, start + len + 1);
			return (word);
		}
		minish->i++;
		len++;
	}
	return (ft_putstr_fd("Error: unclosed quote\n", 2), NULL);
}
