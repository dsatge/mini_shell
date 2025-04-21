/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:28 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 18:15:34 by enschnei         ###   ########.fr       */
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

char	*redir_pipe_to_word(char *buffer, int *i)
{
	char	*word;

	word = NULL;
	if (buffer[*i] == '|')
		word = ft_strdup("|");
	else if (buffer[*i] == '<')
		word = handle_less(buffer, i);
	else if (buffer[*i] == '>')
		word = handle_great(buffer, i);
	if (!word)
		return (NULL);
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
