/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:10:34 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/29 17:57:54 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_type(t_token *element)
{
	if (ft_ispipe(*element) == 0)
		element->type = pip;
	else if (ft_isredir(*element) == 0)
		element->type = redir;
	else
		element->type = word;
}

int	ft_ispipe(t_token element)
{
	if (element.str == NULL)
		exit(EXIT_FAILURE); 
	if(element.str[0] == '|' && element.str[1] == '\0')
		return (0);
	else
		return (1);
}

int	ft_isredir(t_token element)
{
	if (element.str == NULL)
		exit(EXIT_FAILURE);
	if(element.str[0] == '>' && element.str[1] == '>')
	{
		if (element.str[2] == '\0')
			return (0);
	}
	else if(element.str[0] == '<' && element.str[1] == '<') 
	{
		if (element.str[2] == '\0')
			return (0);
	}
	else if(element.str[0] == '<' || element.str[0] == '>')
	{
		if (element.str[1] == '\0')
			return (0);
	}
	return (1);
}

char	*word_from_str(char *buffer, int start, int len)
{
	char	*word;
	int		i;
	
	i = 0;
	word = malloc(sizeof(char) * (len) + 1);
	if (!word)
		return (ft_putstr_fd("Error malloc: word_from_str\n", 2), NULL);
	while (i < len)
	{
		word[i] = buffer[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}