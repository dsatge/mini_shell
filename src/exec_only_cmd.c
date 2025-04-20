/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_only_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:50:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/20 17:18:16 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_o_cmd	*fill_new_node(t_o_cmd *new_node, char **cmds)
{
	int	i;

	i = 0;
	new_node = ft_calloc(sizeof(t_o_cmd), 1);
	if (!new_node)
		return (NULL);
	if (cmds == NULL)
	{
		new_node->tab = NULL;
		return (new_node);
	}
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

static char	**fake_tab(void)
{
	char	**tab;

	tab = ft_calloc(sizeof(char *), 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("");
	if (!tab[0])
		return (free(tab), NULL);
	tab[1] = 0;
	return (tab);
}

t_o_cmd	*ft_only_cmd(t_list *cmds)
{
	t_list	*list;
	t_o_cmd	*head;
	t_o_cmd	*current;
	t_o_cmd	*new_node;
	bool	found_word;

	list = cmds;
	head = NULL;
	current = NULL;
	if (!list || !list->cmd.tab[0])
		return (NULL);
	while (list)
	{
		
		found_word = false;
		if (list->cmd.type == pip)
			list = list->next;
		while (list && list->cmd.type != pip)
		{
			if (list->cmd.type == word)
			{
				new_node = fill_new_node(new_node, list->cmd.tab);
				if (!new_node)
					return (NULL);
				head = headinit_currnext(head, new_node, current);
				current = new_node;
				found_word = true;
			}
			list = list->next;
		}
		if (found_word == false)
		{
			new_node = fill_new_node(new_node, fake_tab());
			if (!new_node)
				return (NULL);
			head = headinit_currnext(head, new_node, current);
			current = new_node;
		}
		if (list)
			list = list->next;
	}
	return (head);
}
