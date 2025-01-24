/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/24 15:59:00 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_list(t_token *list)
{
	t_token *tmp;
    
	tmp = NULL;
	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
		{
			printf("freed list: %s\n", tmp->str);
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
			printf("cmds\n");
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
		printf("freed from tab in cmd : %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
}