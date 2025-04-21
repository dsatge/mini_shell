/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:11:40 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 22:17:03 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_pipes(t_list *node)
{
	while (node && node->cmd.type == pip)
		node = node->next;
	return (node);
}

void	create_fake_node(t_o_cmd **head, t_o_cmd **current)
{
	t_o_cmd	*new_node;
	char	**tab_fake;

	tab_fake = fake_tab();
	new_node = fill_new_node(NULL, tab_fake);
	free_tab(tab_fake);
	if (!new_node)
		return ;
	*head = headinit_currnext(*head, new_node, *current);
	*current = new_node;
}

void	process_command_segment(t_list **node, t_o_cmd **head,
		t_o_cmd **current)
{
	bool	found_word;
	t_o_cmd	*new_node;

	found_word = false;
	while (*node && (*node)->cmd.type != pip)
	{
		if ((*node)->cmd.type == word)
		{
			new_node = fill_new_node(NULL, (*node)->cmd.tab);
			if (!new_node)
				return ;
			*head = headinit_currnext(*head, new_node, *current);
			*current = new_node;
			found_word = true;
		}
		*node = (*node)->next;
	}
	if (!found_word)
		create_fake_node(head, current);
}

t_o_cmd	*ft_only_cmd(t_list *cmds)
{
	t_o_cmd	*head;
	t_o_cmd	*current;

	head = NULL;
	current = NULL;
	while (cmds)
	{
		cmds = skip_pipes(cmds);
		if (!cmds)
			break ;
		process_command_segment(&cmds, &head, &current);
		if (cmds)
			cmds = cmds->next;
	}
	return (head);
}
