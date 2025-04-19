/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/19 18:00:52 by enschnei         ###   ########.fr       */
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
	list = NULL;
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

static void	free_tpipe(t_pipe *pipex)
{
	if (!pipex)
		return ;
	if (pipex->env)
		free_tab(pipex->env);
	if (pipex->path)
		free_tab(pipex->path);
	free(pipex);
	return ;
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

void	free_all(t_minish *minish, bool clean_env)
{
	if (!minish)
		return ;
	free_list(minish->element_head);
	minish->element_head = NULL;
	free_tpipe(minish->pipex);
	minish->pipex = NULL;
	free_cmds(minish->cmds);
	minish->cmds = NULL;
	free_tocmd(minish->o_cmd);
	minish->o_cmd = NULL;
	if (clean_env == true)
	{
		free_env(&minish->env);
		free(minish);
	}
}

void test_print_tab(char **tab)
{
	if (!tab)
		return;
	int i = -1;
	while (tab[++i])
		printf(" %s | %p \n", tab[i], &tab[i]);
}

// void test_print_list()
