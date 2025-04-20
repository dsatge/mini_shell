/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/19 19:55:49 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checktype_order(t_token *element)
{
	if (element->type == pip)
	{
		g_error_code = 2;
		return (ft_printf(2, "bash: syntax error near unexpected  token `|'\n",
				2), EXIT_FAILURE);
	}
	while (element->next != NULL)
	{
		if (element->type == redir && element->next->type != word)
		{
			g_error_code = 2;
			return (ft_printf(2, "Error: redir not followed by word\n", 2), 1);
		}
		if (element->type == pip && element->next->type == pip)
			return (ft_printf(2, "Error: 2 pipes\n", 2), 1);
		element = element->next;
	}
	if (element->type == pip || element->type == redir)
	{
		g_error_code = 2;
		return (ft_printf(2, "bash: syntax error near unexpected token `newline'\n", 2), 1);
	}
	return (0);
}

t_token	*ft_tokenise_pipe_redir(char *word, t_minish *mini_struct,
		int first_word, int quote_typ)
{
	t_token	*new_node;

	if (first_word == 0)
	{
		mini_struct->element->str = word;
		ft_token_type(mini_struct->element, quote_typ);
		mini_struct->element->next = NULL;
	}
	else
	{
		while (mini_struct->element->next)
			mini_struct->element = mini_struct->element->next;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
		new_node->next = NULL;
		new_node->str = word;
		if (!new_node->str)
			return (NULL);
		ft_token_type(new_node, quote_typ);
		mini_struct->element->next = new_node;
		mini_struct->element = mini_struct->element->next;
	}
	return (mini_struct->element);
}

t_token	*ft_tokenise_word(char *word, t_minish *mini_struct, int first_word,
		int quote_typ)
{
	t_token	*new_node;

	if (first_word == 0)
	{
		mini_struct->element_head = mini_struct->element;
		mini_struct->element->str = word;
		mini_struct->element->quote_t = quote_typ;
		ft_token_type(mini_struct->element, quote_typ);
		mini_struct->element->next = NULL;
	}
	else
	{
		while (mini_struct->element->next)
			mini_struct->element = mini_struct->element->next;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
		new_node->next = NULL;
		new_node->str = word;
		new_node->quote_t = quote_typ;
		if (!new_node->str)
			return (NULL);
		new_node->type = 2;
		mini_struct->element->next = new_node;
		mini_struct->element = mini_struct->element->next;
	}
	return (mini_struct->element);
}
