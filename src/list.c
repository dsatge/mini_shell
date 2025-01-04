/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/19 13:46:21 by dsatge           ###   ########.fr       */
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
		cmds->cmd = ft_cmd(list);//ft t_cmd add tab
		if (!cmds->key_p.)
			cmds->key_p->head = cmds;
		cmds->key_p->list_len++;
		cmds->prev = cmds;
		cmds = cmds->next;
		cmds->key_p->tail = cmds;
		cmds->next = NULL;
		while (list || list->type != pip)
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

t_cmd	*ft_cmd(t_token *list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->tab = tab_cmds(list); //ajouter fonction tableau cmds
	return (cmd);
}

char **tab_cmds(t_token *list)
{
	int		tab_len;
	int		i;
	t_token	*current;
	char	**tab;

	tab_len = 0;
	i = 0;
	current = list;
	while (current || current->type != pip)
	{
		tab_len++;
		current = current->next;
	}
	current = list;
	tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!tab)
		return (NULL);
	while (current || current->type != pip)
	{
		tab[i] = ft_strdup(current->str);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
