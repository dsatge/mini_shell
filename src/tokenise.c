/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 16:50:58 by dsatge           ###   ########.fr       */
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
			return (ft_printf(2, "Error: multi pipes\n", 2), 1);
		element = element->next;
	}
	if (element->type == pip || element->type == redir)
	{
		g_error_code = 2;
		return (ft_printf(2,
				"bash: syntax error near unexpected token `newline'\n", 2), 1);
	}
	return (0);
}

t_token	*ft_tokenise_pipe_redir(char *word, t_minish *mini_struct)
{
	t_token	*new_node;

	if (mini_struct->count_word == 0)
	{
		mini_struct->element_head = mini_struct->element;
		mini_struct->element->str = word;
		ft_token_type(mini_struct->element, 0);
		mini_struct->element->next = NULL;
	}
	else
	{
		while (mini_struct->element->next)
			mini_struct->element = mini_struct->element->next;
		new_node = ft_calloc(sizeof(t_token), 1);
		if (!new_node)
			return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
		new_node->next = NULL;
		new_node->str = word;
		if (!new_node->str)
			return (NULL);
		ft_token_type(new_node, 0);
		mini_struct->element->next = new_node;
		mini_struct->element = mini_struct->element->next;
	}
	return (mini_struct->element);
}

static t_token	*add_token_to_list(t_minish *mini_struct, char *word,
		int quote_typ)
{
	t_token	*new_node;

	while (mini_struct->element->next)
		mini_struct->element = mini_struct->element->next;
	new_node = ft_calloc(sizeof(t_token), 1);
	if (!new_node)
		return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
	new_node->str = word;
	new_node->quote_t = quote_typ;
	new_node->type = 2;
	new_node->next = NULL;
	mini_struct->element->next = new_node;
	mini_struct->element = new_node;
	return (new_node);
}

t_token	*ft_tokenise_word(char *word, t_minish *mini_struct)
{
	if (mini_struct->count_word == 0)
	{
		mini_struct->element_head = mini_struct->element;
		mini_struct->element->str = word;
		mini_struct->element->quote_t = mini_struct->quote_t;
		ft_token_type(mini_struct->element, mini_struct->quote_t);
		mini_struct->element->next = NULL;
	}
	else
		add_token_to_list(mini_struct, word, mini_struct->quote_t);
	return (mini_struct->element);
}
