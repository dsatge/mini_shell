/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/17 14:33:59 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmds_list(t_token *list, t_list *cmds)
{
	int		skip;
	int		i;

	i = 0;
	skip = 0;
	skip = init_cmds_list(cmds, list, skip);
	if (skip == -1)
		return (-1);
	while (list)
	{
		if (i > 0)
			if (add_new_cmd_node(list, &cmds, &skip) == -1)
				return (-1);
		while (skip > 0)
		{
			list = list->next;
			skip--;
		}
		i++;
	}
	return (0);
}

int	init_cmds_list(t_list *cmds, t_token *list, int skip)
{
	cmds->next = NULL;
	cmds->prev = NULL;
	cmds->head = NULL;
	cmds->cmd_nbr = 1;
	cmds->cmd = NULL;
	if (!list)
		return (-1);
	else
	{
		skip += ft_cmd(list, cmds, 1);
		cmds->head = cmds;
		if (cmds->head->cmd_nbr != 1)
			printf("OUUUUPSSSIIIIII\n");
	}
	return (skip);
}

int	redir_cmds(t_token *list, t_list *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (-1);
	cmds->cmd->type = redir;
	cmds->cmd->tab = ft_calloc(sizeof(char *), (3));
	if (!cmds->cmd->tab)
		return (-1);
	while (i < 2)
	{
		cmds->cmd->tab[i] = ft_strdup(list->str);
		if (!cmds->cmd->tab[i])
			return (-1);
		i++;
		list = list->next;
	}
	cmds->cmd->tab[i] = 0;
	return (2);
}

int	word_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	t_token	*current;

	tab_len = 0;
	current = list;
	cmds->cmd->type = word;
	while (current && current->type == word)
	{
		tab_len++;
		current = current->next;
	}
	if (fill_cmd_tab(list, cmds, tab_len) == -1)
		return (-1);
	return (tab_len);
}

int	pipe_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	t_token	*current;

	tab_len = 1;
	current = list;
	cmds->cmd->type = pip;
	cmds->cmd->tab = ft_calloc(sizeof(char *), (tab_len + 1));
	if (!cmds->cmd->tab)
		return (-1);
	cmds->cmd->tab[0] = ft_strdup("|");
	if (!cmds->cmd->tab[0])
		return (-1);
	cmds->cmd->tab[1] = 0;
	current = current->next;
	return (tab_len);
}
