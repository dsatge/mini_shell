/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:28 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 17:05:15 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_type(char c)
{
	if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else
		return (0);
}

bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
	{
		return (true);
	}
	return (false);
}

bool	is_redir_pipe(char c, t_minish *minish)
{
	if (c == '|')
	{
		minish->pipex->nbr_cmds++;
		return (true);
	}
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

char	*redir_pipe_to_word(char *buffer, t_minish *mini_struct)
{
	char	*word;

	word = NULL;
	if (buffer[mini_struct->i] == '|')
		word = ft_strdup("|");
	else if (buffer[mini_struct->i] == '<')
		word = handle_less(buffer, mini_struct);
	else if (buffer[mini_struct->i] == '>')
		word = handle_great(buffer, mini_struct);
	if (!word)
		return (NULL);
	mini_struct->i = mini_struct->i + 1;
	return (word);
}

char	*letters_to_word(char *word, char *buffer, int start, int i)
{
	char	*joined_letters;
	char	*joined_word;

	if (start == 1)
		return (word);
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
