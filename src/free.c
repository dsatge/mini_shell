/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/10 17:18:51 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *list)
{
	t_token	*tmp;

	tmp = NULL;
	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
		{
			free(tmp->str);
		}
		free(tmp);
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*tmp;

	cmds = cmds->head;
	while (cmds)
	{
		if (cmds)
		{
			if (cmds->cmd && cmds->cmd->tab)
				free_tab(cmds->cmd->tab);
			if (cmds->cmd && cmds->cmd->tab)
				free(cmds->cmd->tab);
			if (cmds->cmd)
				free(cmds->cmd);
		}
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
	free(cmds);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}
