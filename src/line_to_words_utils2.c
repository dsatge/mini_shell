/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:43:16 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/17 15:45:34 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_less_redirection(char *buffer, int *i)
{
	char	*word;

	word = NULL;
	if (buffer[*i] == '<' && buffer[*i + 1] == '<')
	{
		*i = *i + 1;
		word = ft_strdup("<<");
	}
	else
		word = ft_strdup("<");
	if (!word)
		return (NULL);
	return (word);
}

char	*handle_greater_redirection(char *buffer, int *i)
{
	char	*word;

	word = NULL;
	if (buffer[*i] == '>' && buffer[*i + 1] == '>')
	{
		*i = *i + 1;
		word = ft_strdup(">>");
		if (!word)
			return (NULL);
	}
	else
		word = ft_strdup(">");
	if (!word)
		return (NULL);
	return (word);
}

int	handle_quotes(char *buffer, int *i, int *start, char **word)
{
	char	*tmp;
	int		quote_typ;

	tmp = NULL;
	quote_typ = ft_q_type(buffer[*i]);
	if (*start != *i)
	{
		tmp = letters_to_word(*word, buffer, *start, *i);
		if (!tmp)
			return (-1);
	}
	else if (*word && *start == *i)
		tmp = *word;
	*word = ft_join_quotes(buffer, i, tmp);
	if (!*word)
		return (-1);
	if (buffer[*i + 1] && is_redir_pipe(buffer[*i + 1]) == false)
		*start = *i + 1;
	else
		*start = -1;
	return (quote_typ);
}
