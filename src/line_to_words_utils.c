/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:02:28 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/09 14:27:38 by enschnei         ###   ########.fr       */
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
