/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:17:03 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/09 16:02:45 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_dir_list	*add_cmd_node(t_dir_list *cmd_list, t_token *token_list)
{
	t_dir_list	*new_node;

	if (!token_list)
		return (NULL);
	while (cmd_list && cmd_list->next_dir)
		cmd_list = cmd_list->next_dir;
	new_node = malloc(sizeof(t_dir_list));
	if (!new_node)
		return (ft_putstr_fd("Error malloc add_cmd_node\n", 2), NULL);
	new_node->element = token_list;
	new_node->next_dir = NULL;
	if (cmd_list)
		cmd_list->next_dir = new_node;
	return (new_node);
}

t_dir_list	*ft_dir_list(t_minish *mini_struct, t_token *token_list)
{
	t_dir_list	*cmd_list;
	t_dir_list	*head;

	(void)mini_struct;
	cmd_list = NULL;
	head = NULL;
	if (!token_list)
		return (ft_putstr_fd("Error no element in ft_dir_list\n", 2), NULL);
	while (token_list)
	{
		while (token_list->next && token_list->type != redir)
			token_list = token_list->next;
		if (token_list->type == redir)
			cmd_list = add_cmd_node(cmd_list, token_list);
		if (head == NULL)
			head = cmd_list;
		token_list = token_list->next;
	}
	return (head);
}
