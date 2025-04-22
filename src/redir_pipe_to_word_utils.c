/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe_to_word_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:11:09 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 23:26:48 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_less(char *buffer, t_minish *minish)
{
	char	*word;

	if (buffer[minish->i] == '<' && buffer[minish->i + 1] == '<')
	{
		minish->i = minish->i + 1;
		word = ft_strdup("<<");
	}
	else
		word = ft_strdup("<");
	return (word);
}

char	*handle_great(char *buffer, t_minish *minish)
{
	char	*word;

	if (buffer[minish->i] == '>' && buffer[minish->i + 1] == '>')
	{
		minish->i = minish->i + 1;
		word = ft_strdup(">>");
	}
	else
		word = ft_strdup(">");
	return (word);
}
