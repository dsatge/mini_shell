/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:29:27 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/06 18:45:53 by dsatge           ###   ########.fr       */
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
		}
		else
			word = ft_strdup("<");
	}
	else if (buffer[*i] == '>')
	{
		if (buffer[*i] == '>' && buffer[*i + 1] == '>')
		{
			*i = *i + 1;
			word = ft_strdup(">>");
		}
		else
			word = ft_strdup(">");
	}
	*i = *i + 1;
	return (word);
}

char	*ft_quotes(char *buffer, int *i)
{
	int len;
	int	start;
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
		if (buffer[*i] == '"' && quote == DOUBLE_QUOTE)
		{
			word = word_from_str(buffer, start + 1, start + len + 1);
			return (word);
		}
		if (buffer[*i] == '\'' && quote == SINGLE_QUOTE)
		{
			word = word_from_str(buffer, start + 1, start + len + 1);	
			return (word);
		}
        *i = *i + 1;
		len++;
	}
	return (ft_putstr_fd("Error: unclosed quote\n", 2), NULL);
}


int	is_word(char *buffer, int *i, t_minish **mini_struct, int first_word)
{
	char	*word;
	char	*tmp;
	int		start;

	word = NULL;
	start = *i;
	printf("|||||||||||| i = %i = %c", *i, buffer[*i]);
	if (is_redir_pipe(buffer[*i]) == true)
	{
		word = redir_pipe_to_word(buffer, i);
		return (ft_tokenise_pipe_redir(word, *mini_struct, first_word), 0);
	}
	while (buffer[*i] && is_redir_pipe(buffer[*i]) == false && is_White_Space(buffer[*i]) == false)
	{
		if (buffer[*i] == '\'' || buffer[*i] == '"')
		{
			if (start != *i)
			{
				tmp = letters_to_word(word, buffer, start, *i);
				if (!tmp)
					return (-1);
			}
			else if (word && start == *i)
				tmp = word;
			word = ft_join_quotes(buffer, i, tmp);
			if (!word)
				return (-1);
			if (buffer[*i + 1] && is_redir_pipe(buffer[*i + 1]) == false)
				start = *i + 1;
			else
				start = -1;
		}
		*i = *i + 1;
	}
	if (start != *i && start != -1)
		word = letters_to_word(word, buffer, start, *i);
	return (ft_tokenise_word(word, *mini_struct, first_word), 0);
}

char	*letters_to_word(char *word, char *buffer, int start, int i)
{
	char *joined_letters;
	char	*joined_word;
	
	joined_letters = word_from_str(buffer, start, i);
	if (!joined_letters)
		return (ft_putstr_fd("Error malloc: letters_to_word\n", 2), NULL);
	if (word)
	{
		joined_word = ft_strjoin(word, joined_letters);
		return (free(word), free(joined_letters), joined_word);
	}
	return (joined_letters);
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
		return (free(quote_word), free(tmp), joined_words);
	}
	return (quote_word);
}

t_token	*ft_split_word(char *buffer, t_minish *mini_struct)
{
	int i;
	int	word;
	int	first_word;
	t_token	*head;

    i = 0;
	word = 0;
	first_word = 0;
	mini_struct->element = malloc(sizeof(t_token));
	if (!mini_struct)
		return (NULL);
	mini_struct->element->str = NULL;
	head = mini_struct->element;
	while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
		i++;
	while (buffer[i]){
		if (is_word(buffer, &i, &mini_struct, first_word) == -1)
			return (head);
		first_word++;
        while ((is_White_Space(buffer[i]) == true) && buffer[i] != '\0')
			i++;
    }
    return (head);
}
