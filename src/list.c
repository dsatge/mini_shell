/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/09 16:45:53 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_list	*cmds_list(t_token *list)
{
	t_list  *cmds;

	cmds = malloc(sizeof(t_list));
	if (!cmds)
		return (NULL);
	if (init_cmds_list(cmds) == -1)
		return (NULL);
	while (list)
	{
		ft_cmd(list, cmds->cmd);//ft t_cmd add tab
		if (!cmds->key_p->head)
			cmds->key_p->head = &cmds->cmd;
		cmds->key_p->list_len++;
		cmds->prev = cmds;
		cmds->key_p->tail = &cmds->cmd;
		cmds->next = NULL;
		cmds = cmds->next;
		while (list && list->type != pip)
			list = list->next;
	}
	return (cmds);
}

int	init_cmds_list(t_list *cmds)
{
	cmds->prev = NULL;
	cmds->next = NULL;
	cmds->cmd = NULL;
	cmds->key_p = malloc(sizeof(t_structlist));
	if (!cmds->key_p)
		return (-1);
	cmds->key_p->head = NULL;
	cmds->key_p->tail = NULL;
	cmds->key_p->list_len = 0;
	return (0);
}

int	ft_cmd(t_token *list, t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (-1);
	if (tab_cmds(list, cmd->tab) == -1)
		return (-1); //ajouter fonction tableau cmds
	return (0);
}

int	tab_cmds(t_token *list, char **tab)
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
	tab = calloc(sizeof(char *), (tab_len + 1));
	if (!tab)
		return (-1);
	while (current && current->type != pip)
	{
		tab[i] = ft_strdup(current->str);
		i++;
		current = current->next;
	}
	tab[i] = 0;
	return (0);
}
