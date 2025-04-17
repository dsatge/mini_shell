/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/17 15:44:35 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quotes(char *buffer, int *i)
{
	int		len;
	int		start;
	char	*word;
	t_quote	quote;

	len = 0;
	start = *i;
	if (buffer[*i] == '"')
		quote = DOUBLE_QUOTE;
	if (buffer[*i] == '\'')
		quote = SINGLE_QUOTE;
	*i = *i + 1;
	while (buffer[*i])
	{
		if ((buffer[*i] == '"' && quote == DOUBLE_QUOTE) || (buffer[*i] == '\''
				&& quote == SINGLE_QUOTE))
		{
			word = word_from_str(buffer, start + 1, start + len + 1);
			return (word);
		}
		*i = *i + 1;
		len++;
	}
	return (ft_putstr_fd("Error: unclosed quote\n", 2), NULL);
}

int	ft_q_type(char c)
{
	t_quote_type	quote;

	quote = no_q;
	if (c == '"')
		quote = double_q;
	if (c == '\'')
		quote = single_q;
	return (quote);
}

int	is_word(char *buffer, int *i, t_minish **mini_struct, int first_word)
{
	char	*word;
	int		start;
	int		quote_typ;

	word = NULL;
	start = *i;
	if (is_redir_pipe(buffer[*i]) == true)
	{
		word = redir_pipe_to_word(buffer, i);
		return (ft_tokenise_pipe_redir(word, *mini_struct, first_word), 0);
	}
	while (buffer[*i] && is_redir_pipe(buffer[*i]) == false
		&& is_white_space(buffer[*i]) == false)
	{
		if (buffer[*i] == '\'' || buffer[*i] == '"')
		{
			quote_typ = handle_quotes(buffer, i, &start, &word);
			if (quote_typ == -1)
				return (-1);
		}
		*i = *i + 1;
	}
	if (start != *i && start != -1)
		word = letters_to_word(word, buffer, start, *i);
	return (ft_tokenise_word(word, *mini_struct, first_word, quote_typ), 0);
}

char	*ft_join_quotes(char *buffer, int *i, char *tmp)
{
	char	*quote_word;
	char	*joined_words;

	joined_words = NULL;
	quote_word = ft_quotes(buffer, i);
	if (!quote_word)
		return (ft_putstr_fd("Error malloc: ft_join_quotes", 2), NULL);
	if (tmp)
	{
		joined_words = ft_strjoin(tmp, quote_word);
		if (!joined_words)
			return (ft_putstr_fd("Error ft_strjoin: ft_join_quotes", 2), NULL);
		return (free(quote_word), free(tmp), joined_words);
	}
	return (quote_word);
}

t_token	*ft_split_word(char *buffer, t_minish *mini_struct)
{
	int		i;
	int		first_word;
	t_token	*head;

	i = 0;
	first_word = 0;
	mini_struct->element = malloc(sizeof(t_token));
	if (!mini_struct->element)
		return (NULL);
	mini_struct->element->str = NULL;
	mini_struct->element->quote_t = 0;
	head = mini_struct->element;
	while ((is_white_space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
	while (buffer[i])
	{
		if (is_word(buffer, &i, &mini_struct, first_word) == -1)
			return (head);
		first_word++;
		while ((is_white_space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
	}
	return (head);
}
