/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/16 18:28:38 by dsatge           ###   ########.fr       */
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

	if (!cmds)
		return ;
	cmds = cmds->head;
	while (cmds)
	{
		if (cmds)
		{
			if (cmds->cmd && cmds->cmd->tab)
				free_tab(cmds->cmd->tab);
		}
		tmp = cmds;
		cmds = cmds->next;
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
		i++;
	}
	free(tab);
}

static void	free_tpipe(t_pipe *pipex)
{
	if (!pipex)
		return ;
	if (pipex->env)
		free_tab(pipex->env);
	if (pipex->path)
		free_tab(pipex->path);
	return ;
}

void	free_tocmd(t_o_cmd *o_cmd)
{
	t_o_cmd	*tmp;

	if (!o_cmd)
		return ;
	while (o_cmd)
	{
		tmp = o_cmd;
		o_cmd = o_cmd->next;
		free_tab(tmp->tab);
		free(tmp);
	}
	return ;
}


void	free_all(t_minish *minish, bool clean_env)
{
	if (!minish)
		return ;
	free_list(minish->element);
	free_tpipe(minish->pipex);
	free_cmds(minish->cmds);
	free_tocmd(minish->o_cmd);
	if (clean_env == true)
		free_env(&minish->env);
}