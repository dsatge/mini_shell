/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/06 19:11:26 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checktype_order(t_token *element)
{
	if (element->type == pip)
		return (ft_putstr_fd("Error: 1st is pipe\n", 2), -1);
	while (element->next != NULL)
	{
		if (element->type == redir && element->next->type != word)
			return (ft_putstr_fd("Error: redir not followed by word\n", 2), -1);
		if (element->type == pip && element->next->type == pip)
			return (ft_putstr_fd("Error: 2 pipes\n", 2),1);
		element = element->next;
	}
	if (element->type == pip || element->type == redir)
		return (ft_putstr_fd("Error: not ending by word\n", 2), -1);
	return (0);
}

t_token	*ft_tokenise_pipe_redir(char *word, t_minish *mini_struct, int first_word)
{
	t_token	*new_node;

	printf(" received = %s\n", word);
	if (first_word == 0)
	{
		mini_struct->element->str = word;
		ft_token_type(mini_struct->element);
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
		ft_token_type(new_node);
		mini_struct->element->next = new_node;
		mini_struct->element= mini_struct->element->next;
	}
	return (mini_struct->element);
}


t_token	*ft_tokenise_word(char *word, t_minish *mini_struct, int first_word)
{
	t_token	*new_node;

	printf("received = %s\n", word);
	if (first_word == 0)
	{
		mini_struct->element->str = word;
		ft_token_type(mini_struct->element);
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
		new_node->type = 2;
		mini_struct->element->next = new_node;
		mini_struct->element= mini_struct->element->next;
	}
	return (mini_struct->element);
}

t_command_list	*ft_cmd_list(t_minish *mini_struct, t_token *token_list)
{
	t_command_list	*cmd_list;
	t_command_list	*head;

	(void)mini_struct;
	cmd_list = NULL;
	head = NULL;
	if (!token_list)
		return (ft_putstr_fd("Error no element in ft_cmd_list\n", 2), NULL);
	while (token_list)
	{
		cmd_list = add_cmd_node(cmd_list, token_list);
		if (head == NULL)
			head = cmd_list;
		while (token_list->next && token_list->type != pip)
			token_list = token_list->next;
		if (!token_list->next)
			break;	
		token_list = token_list->next;
	}
	return (head);
}

t_command_list	*add_cmd_node(t_command_list *cmd_list, t_token *token_list)
{
	t_command_list	*new_node;

	if (!token_list)
		return (NULL);
	while (cmd_list && cmd_list->next_cmd)
		cmd_list = cmd_list->next_cmd;
	new_node = malloc(sizeof(t_command_list));
	if (!new_node)
		return (ft_putstr_fd("Error malloc add_cmd_node\n", 2), NULL);
	new_node->element = token_list;
	new_node->next_cmd = NULL;
	if (cmd_list)
		cmd_list->next_cmd = new_node;
	return (new_node);
}
