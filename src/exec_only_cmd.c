/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_only_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:50:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 22:17:18 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_o_cmd	*fill_new_node(t_o_cmd *new_node, char **cmds)
{
	int	i;

	i = 0;
	new_node = ft_calloc(sizeof(t_o_cmd), 1);
	if (!new_node)
		return (free_tab(cmds), NULL);
	if (cmds == NULL)
	{
		new_node->tab = NULL;
		return (new_node);
	}
	new_node->tab = ft_calloc(sizeof(char *), ft_count_line_split(cmds) + 1);
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

t_o_cmd	*headinit_currnext(t_o_cmd *head, t_o_cmd *new_node,
		t_o_cmd *current)
{
	if (head == NULL)
		head = new_node;
	else
		current->next = new_node;
	return (head);
}

char	**fake_tab(void)
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
