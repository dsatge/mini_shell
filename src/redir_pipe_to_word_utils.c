/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe_to_word_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:11:09 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 18:13:14 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_less(char *buffer, int *i)
{
	char	*word;

	if (buffer[*i] == '<' && buffer[*i + 1] == '<')
	{
		*i = *i + 1;
		word = ft_strdup("<<");
	}
	else
		word = ft_strdup("<");
	return (word);
}

char	*handle_great(char *buffer, int *i)
{
	char	*word;

	if (buffer[*i] == '>' && buffer[*i + 1] == '>')
	{
		*i = *i + 1;
		word = ft_strdup(">>");
	}
	else
		word = ft_strdup(">");
	return (word);
}
