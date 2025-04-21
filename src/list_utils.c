/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:43:23 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 22:00:55 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_and_fill_next_cmd(t_token **list, t_list **cmds, int *skip)
{
	t_list	*tmp;

	tmp = *cmds;
	(*cmds)->next = ft_calloc(sizeof(t_list), 1);
	if (!(*cmds)->next)
		return (ft_putstr_fd("ERROR : malloc fail", 2), -1);
	*cmds = (*cmds)->next;
	(*cmds)->head = tmp->head;
	*skip = ft_cmd(*list, *cmds, tmp->head->cmd_nbr);
	(*cmds)->next = NULL;
	(*cmds)->prev = tmp;
	while (*skip > 0)
	{
		*list = (*list)->next;
		(*skip)--;
	}
	return (0);
}

int	cmds_list(t_token *list, t_list *cmds)
{
	int	skip;
	int	i;

	skip = 0;
	i = 0;
	skip = init_cmds_list(cmds, list, skip);
	if (skip == -1)
		return (-1);
	while (list)
	{
		if (i++ > 0)
		{
			if (create_and_fill_next_cmd(&list, &cmds, &skip) == -1)
				return (-1);
		}
		else
		{
			while (skip > 0)
			{
				list = list->next;
				skip--;
			}
		}
	}
	return (0);
}

int	pipe_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	t_token	*current;

	tab_len = 1;
	current = list;
	cmds->cmd.type = pip;
	cmds->cmd.tab = ft_calloc(sizeof(char *), (tab_len + 1));
	if (!cmds->cmd.tab)
		return (-1);
	cmds->cmd.tab[0] = ft_strdup("|");
	if (!cmds->cmd.tab[0])
		return (-1);
	cmds->cmd.tab[1] = 0;
	current = current->next;
	return (tab_len);
}

int	count_word_tokens(t_token *list)
{
	int	count;

	count = 0;
	while (list && list->type == word)
	{
		count++;
		list = list->next;
	}
	return (count);
}
