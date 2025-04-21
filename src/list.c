/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:36:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/20 19:49:21 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmds_list(t_token *list, t_list *cmds)
{
	t_list	*tmp;
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
		{
			tmp = cmds;
			cmds->next = ft_calloc(sizeof(t_list), 1);
			if (!cmds->next)
				return (ft_putstr_fd("ERROR : malloc fail", 2), -1);
			cmds = cmds->next;
			cmds->head = tmp->head;
			skip = ft_cmd(list, cmds, tmp->head->cmd_nbr);
			cmds->next = NULL;
			cmds->prev = tmp;
		}
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
	ft_bzero(cmds, sizeof(t_list));
	cmds->cmd_nbr = 1;
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

int	ft_cmd(t_token *list, t_list *cmds, int nbr_cmd)
{
	int	element;

	element = 0;
	if (cmds && cmds->head == NULL)
	{
		cmds->head = cmds;
		cmds->head->cmd_nbr = nbr_cmd;
	}
	element = tab_cmds(list, cmds);
	if (element == -1)
		return (-1);
	return (element);
}

int	tab_cmds(t_token *list, t_list *cmds)
{
	int		list_element;
	int		run_loop;
	t_token	*current;
	t_list	*curr_cmds;

	list_element = 0;
	current = list;
	curr_cmds = cmds;
	run_loop = 0;
	if (current->type == pip)
	{
		list_element += pipe_cmds(current, curr_cmds);
		// current = current->next;
		if (cmds->head)
		{
			cmds->head->cmd_nbr += 1;
		}
	}
	if (current->type == redir)
	{
		run_loop = 1;
		list_element += redir_cmds(current, curr_cmds);
	}
	if (run_loop == 0 && current->type == word)
	{
		list_element += word_cmds(current, curr_cmds);
		run_loop = 1;
	}
	return (list_element);
}

int	redir_cmds(t_token *list, t_list *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (-1);
	cmds->cmd.type = redir;
	cmds->cmd.tab = ft_calloc(sizeof(char *), (3));
	if (!cmds->cmd.tab)
		return (-1);
	while (i < 2)
	{
		cmds->cmd.tab[i] = ft_strdup(list->str);
		if (!cmds->cmd.tab[i])
			return (-1);
		i++;
		list = list->next;
	}
	cmds->cmd.tab[i] = 0;
	return (2);
}

int	word_cmds(t_token *list, t_list *cmds)
{
	int		tab_len;
	int		i;
	t_token	*current;

	tab_len = 0;
	i = 0;
	current = list;
	cmds->cmd.type = word;
	while (current && current->type == word)
	{
		tab_len++;
		current = current->next;
	}
	current = list;
	cmds->cmd.tab = ft_calloc(sizeof(char *), (tab_len + 1));
	if (!cmds->cmd.tab)
		return (-1);
	while (current && current->type == word)
	{
		cmds->cmd.tab[i] = ft_strdup(current->str);
		cmds->cmd.quote_t = current->quote_t;
		if (!cmds->cmd.tab[i])
			return (-1);
		i++;
		current = current->next;
	}
	cmds->cmd.tab[i] = 0;
	return (tab_len);
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
