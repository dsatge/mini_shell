/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 02:00:39 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_q_type(char c)
{
	t_quote_type	quote;

	quote = no_q;
	if (c == '"')
		quote = double_q;
	if (c == '\'')
		quote = single_q;
	return (quote);
}

static int	handle_redir_pipe(char *buffer, t_minish **mini_struct)
{
	char	*word;

	if (is_redir_pipe(buffer[(*mini_struct)->i], *mini_struct))
	{
		word = redir_pipe_to_word(buffer, *mini_struct);
		if (!word)
			return (-1);
		ft_tokenise_pipe_redir(word, *mini_struct);
		return (0);
	}
	return (1);
}

int	handle_quotes(char *buffer, int *start, char **word,
	t_minish **mini_struct)
{
	char	*tmp;

	tmp = NULL;
	(*mini_struct)->quote_t = ft_q_type(buffer[(*mini_struct)->i]);
	if (*start != (*mini_struct)->i)
	{
		tmp = letters_to_word(*word, buffer, *start, (*mini_struct)->i);
		if (!tmp)
			return (-1);
	}
	else if (*word && *start == (*mini_struct)->i)
		tmp = *word;
	*word = ft_join_quotes(buffer, *mini_struct, tmp);
	if (!*word)
		return (free(tmp), -1);
	if (buffer[(*mini_struct)->i + 1]
		&& !is_redir_pipe(buffer[(*mini_struct)->i + 1], *mini_struct))
		*start = (*mini_struct)->i + 1;
	else
		*start = -1;
	return (0);
}

int	is_word(char *buffer, t_minish **mini_struct)
{
	char	*word;
	int		start;

	word = NULL;
	start = (*mini_struct)->i;
	if (handle_redir_pipe(buffer, mini_struct) != 1)
		return (0);
	while (buffer[(*mini_struct)->i]
		&& !is_redir_pipe(buffer[(*mini_struct)->i], *mini_struct)
		&& !is_white_space(buffer[(*mini_struct)->i]))
	{
		if (buffer[(*mini_struct)->i] == '\''
			|| buffer[(*mini_struct)->i] == '"')
		{
			if (handle_quotes(buffer, &start, &word, mini_struct) == -1)
				return (-1);
			(*mini_struct)->i++;
		}
		else
			(*mini_struct)->i++;
	}
	if (start != (*mini_struct)->i && start != -1)
		word = letters_to_word(word, buffer, start, (*mini_struct)->i);
	ft_tokenise_word(word, *mini_struct);
	return (0);
}
