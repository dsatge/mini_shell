/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:10:34 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/04 17:39:44 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(t_token element)
{
	// if (element.str == NULL)
	// 	exit(EXIT_FAILURE);
	if(element.str[0] == '|' && element.str[1] == '\0')
		return (0);
	else
		return (1);
}

int	ft_isredir(t_token element)
{
	// if (element.str == NULL)
	// 	exit(EXIT_FAILURE);
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