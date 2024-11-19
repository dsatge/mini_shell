/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:10:34 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/18 19:01:34 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*word_from_str(char *buffer, int start, int end)
{
	char	*word;
	int		i;
	
	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (ft_putstr_fd("Error malloc: word_from_str", 2), NULL);
	while (start < end)
	{
		word[i] = buffer[start];
		i++;
		start++;
	}
	word[i] = '\0';
	printf("in word from str = %s\n", word);
	return (word);
}