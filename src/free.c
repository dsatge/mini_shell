/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 17:39:33 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next;
		free(list->str);
		free(list);
		list = tmp;
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*tmp;

	if (!cmds)
		return ;
	cmds = cmds->head;
	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp)
		{
			if (tmp->cmd.tab)
				free_tab(tmp->cmd.tab);
		}
		free(tmp);
	}
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
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_tocmd(t_o_cmd *o_cmd)
{
	t_o_cmd	*tmp;

	while (o_cmd)
	{
		tmp = o_cmd->next;
		free_tab(o_cmd->tab);
		o_cmd->tab = NULL;
		free(o_cmd);
		o_cmd = tmp;
	}
	return ;
}

void	free_file_names(t_f_name *files)
{
	t_f_name	*tmp;

	if (!files)
		return ;
	while (files)
	{
		tmp = files->next;
		if (files->f_name)
		{
			unlink(files->f_name);
			free(files->f_name);
			free(files);
		}
		files = tmp;
	}
	return ;
}
