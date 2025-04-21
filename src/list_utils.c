/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:43:23 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 21:05:56 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_and_fill_next_cmd(t_token **list, t_list **cmds, int *skip)
{
	t_list *tmp;

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
