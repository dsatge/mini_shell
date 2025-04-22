/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 02:03:13 by enschnei         ###   ########.fr       */
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

char	*ft_join_quotes(char *buffer, int *i, char *tmp)
{
	char	*quote_word;
	char	*joined_words;

	joined_words = NULL;
	quote_word = ft_quotes(buffer, i);
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
	int		i;
	int		first_word;
	t_token	*head;

	i = 0;
	first_word = -1;
	mini_struct->pipex->nbr_cmds = 1;
	mini_struct->element = ft_calloc(sizeof(t_token), 1);
	if (!mini_struct->element)
		return (EXIT_FAILURE);
	head = mini_struct->element;
	if (skip_initial_whitespace(buffer, &i, mini_struct) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_words(buffer, &i, mini_struct, &first_word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (head)
		mini_struct->head_token = head;
	return (EXIT_SUCCESS);

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
