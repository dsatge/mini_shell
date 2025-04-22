/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:10:34 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 02:03:53 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_type(t_token *element, int quote_typ)
{
	if (ft_ispipe(*element) == 0)
		element->type = pip;
	else if (ft_isredir(*element) == 0)
		element->type = redir;
	else
		element->type = word;
	element->quote_t = quote_typ;
}

int	ft_ispipe(t_token element)
{
	if (element.str == NULL)
		exit(EXIT_FAILURE);
	if (element.str[0] == '|' && element.str[1] == '\0')
		return (0);
	else
		return (1);
}

int	ft_isredir(t_token element)
{
	if (element.str == NULL)
		exit(EXIT_FAILURE);
	if (element.str[0] == '>' && element.str[1] == '>')
	{
		if (element.str[2] == '\0')
			return (0);
	}
	else if (element.str[0] == '<' && element.str[1] == '<')
	{
		if (element.str[2] == '\0')
			return (0);
	}
	else if (element.str[0] == '<' || element.str[0] == '>')
	{
		if (element.str[1] == '\0')
			return (0);
	}
	return (1);
}

char	*word_from_str(char *buffer, int start, int end)
{
    char	*word;
    int		i;
    int		length;

    length = end - start;
    word = malloc(sizeof(char) * (length + 1));
    if (!word)
        return (ft_putstr_fd("Error malloc: word_from_str\n", 2), NULL);

    i = 0;
    while (i < length)
    {
        word[i] = buffer[start + i];
        i++;
    }
    word[i] = '\0';
    return (word);
}
