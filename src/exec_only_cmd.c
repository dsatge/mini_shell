/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_only_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:50:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/17 12:26:11 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_o_cmd	*fill_new_node(t_o_cmd *new_node, char **cmds)
{
	int	i;

	i = 0;
	new_node = malloc(sizeof(t_o_cmd));
	if (!new_node)
		return (NULL);
	new_node->tab = ft_calloc(sizeof(char *),
			ft_count_line_split(cmds) + 1);
	if (!new_node->tab)
		return (0);
	while (cmds[i] != 0)
	{
		new_node->tab[i] = ft_strdup(cmds[i]);
		if (!new_node->tab[i])
			return (NULL);
		i++;
	}
	new_node->tab[i] = 0;
	new_node->next = NULL;
	return (new_node);
}

static t_o_cmd	*headinit_currnext(t_o_cmd *head, t_o_cmd *new_node,
	t_o_cmd *current)
{
	if (head == NULL)
		head = new_node;
	else
		current->next = new_node;
	return (head);
}

t_o_cmd	*ft_only_cmd(t_list *cmds)
{
	t_list	*list;
	t_o_cmd	*head;
	t_o_cmd	*current;
	t_o_cmd	*new_node;

	list = cmds;
	head = NULL;
	current = NULL;
	if (!list || !list->cmd.tab[0])
		return (NULL);
	while (list)
	{
		if (list->cmd.type == word)
		{
			new_node = fill_new_node(new_node, list->cmd.tab);
			if (!new_node)
				return (NULL);
			head = headinit_currnext(head, new_node, current);
			current = new_node;
		}
		list = list->next;
	}
	return (head);
}
