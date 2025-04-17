/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:28 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/17 16:59:13 by dsatge           ###   ########.fr       */
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

bool	is_redir_pipe(char c)
{
	if (c == '|')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

char	*redir_pipe_to_word(char *buffer, int *i)
{
	char	*word;
	
	word = NULL;
	if (buffer[*i] == '|')
		word = ft_strdup("|");
	else if (buffer[*i] == '<')
	{
		if (buffer[*i] == '<' && buffer[*i + 1] == '<')
		{
			*i = *i + 1;
			word = ft_strdup("<<");
			if (!word)
				return (NULL);
		}
		else
		{
			word = ft_strdup("<");
			if (!word)
				return (NULL);	
		}
	}
	else if (buffer[*i] == '>')
	{
		if (buffer[*i] == '>' && buffer[*i + 1] == '>')
		{
			*i = *i + 1;
			word = ft_strdup(">>");
			if (!word)
				return (NULL);
		}
		else
		{
			word = ft_strdup(">");
			if (!word)
				return (NULL);
		}	
	}
	*i = *i + 1;
	return (word);
}

char	*letters_to_word(char *word, char *buffer, int start, int i)
{
	char	*joined_letters;
	char	*joined_word;

	joined_letters = word_from_str(buffer, start, i);
	if (!joined_letters)
		return (ft_putstr_fd("Error malloc: letters_to_word\n", 2), NULL);
	if (word)
	{
		joined_word = ft_strjoin(word, joined_letters);
		if (!joined_word)
			return (ft_putstr_fd("Error ft_strjoin: letters_to_word", 2), NULL);
		return (free(word), free(joined_letters), joined_word);
	}
	else
		free(word);
	return (joined_letters);
}
