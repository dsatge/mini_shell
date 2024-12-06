/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:10:34 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/06 19:01:36 by dsatge           ###   ########.fr       */
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
	while ((i + start) < len)
	{
		word[i] = buffer[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

t_command_list	*init_list(char *buffer, t_minish *minish, t_command_list *cmd_list, t_token *tok_list)
{

	if (ft_checktype_order(tok_list) == 0)
	{
		cmd_list = ft_cmd_list(minish, tok_list);
		ft_print_cmdlist(cmd_list);
	}
	else
	{
		free_list(tok_list);
		free(buffer);
		return (NULL);
	}
	return (cmd_list);
}

