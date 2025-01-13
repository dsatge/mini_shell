/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/13 13:54:04 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	cmds_list(t_token *list, t_list *cmds)
{
	t_list *node;
	
	if (init_cmds_list(cmds) == -1)
		return (-1);
	while (list)
	{
		node = malloc(sizeof(t_list));
			if (!node)
				return (-1);
		ft_cmd(list, node);//ft t_cmd add tab
		// node->prev = cmds;
		node->next = NULL;
		while (list && list->type != pip)
			list = list->next;
		if (list && list->type == pip)
			list = list->next;
		cmds->next = node;
		node->prev = cmds;
		cmds = cmds->next;
	}
	while (cmds && cmds->prev)
	{
		printf("CMMMDSSS = %s\n", cmds->cmd->tab[0]);
		cmds = cmds->prev;
	}
	// cmds = cmds->prev;
	// printf("CMDS PREV = %s\n", cmds->prev->cmd->tab[0]);
	// printf("CMMMMDS 2 = %s\n", cmds->next->cmd->tab[0]);
	return (0);
}

int	init_cmds_list(t_list *cmds)
{
	cmds->prev = NULL;
	cmds->next = NULL;
	cmds->cmd = NULL;
	return (0);
}

int	ft_cmd(t_token *list, t_list *cmds)
{
	cmds->cmd = malloc(sizeof(t_cmd));
	if (!cmds->cmd)
		return (-1);
	if (tab_cmds(list, cmds) == -1)
		return (-1); //ajouter fonction tableau cmds
	return (0);
}

int	tab_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	int		i;
	t_token	*current;

	tab_len = 0;
	i = 0;
	current = list;
	while (current && current->type != pip)
	{
		tab_len++;
		current = current->next;
	}
	current = list;
	cmds->cmd->tab = ft_calloc(sizeof(char*), (tab_len + 1));
	if (!cmds->cmd->tab)
		return (-1);
	while (current && current->type != pip)
	{
		cmds->cmd->tab[i] = ft_strdup(current->str);
		printf("tab = %s\n", cmds->cmd->tab[i]);
		i++;
		current = current->next;
	}
	cmds->cmd->tab[i] = 0;
	return (0);
}
