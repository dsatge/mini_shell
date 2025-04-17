/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:50:56 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/17 14:35:08 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmds->head)
			cmds->head->cmd_nbr += 1;
	}
	if (current->type == redir)
	{
		run_loop = 1;
		list_element += redir_cmds(current, curr_cmds);
	}
	if (run_loop == 0 && current->type == word)
		list_element += word_cmds(current, curr_cmds);
	return (list_element);
}

int	ft_cmd(t_token *list, t_list *cmds, int nbr_cmd)
{
	int	element;

	element = 0;
	cmds->cmd = malloc(sizeof(t_cmd));
	if (!cmds->cmd)
		return (-1);
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

int	add_new_cmd_node(t_token *list, t_list **cmds, int *skip)
{
	t_list	*tmp;

	tmp = *cmds;
	tmp->next = malloc(sizeof(t_list));
	if (!tmp->next)
		return (ft_putstr_fd("ERROR : malloc fail", 2), -1);
	*cmds = tmp->next;
	(*cmds)->head = tmp->head;
	*skip = ft_cmd(list, *cmds, tmp->head->cmd_nbr);
	(*cmds)->next = NULL;
	(*cmds)->prev = tmp;
	return (0);
}

int	fill_cmd_tab(t_token *list, t_list *cmds, int tab_len)
{
	t_token	*current;
	int		i;

	i = 0;
	current = list;
	cmds->cmd->tab = ft_calloc(sizeof(char *), tab_len + 1);
	if (!cmds->cmd->tab)
		return (-1);
	while (current && current->type == word)
	{
		cmds->cmd->tab[i] = ft_strdup(current->str);
		if (!cmds->cmd->tab[i])
			return (-1);
		cmds->cmd->quote_t = current->quote_t;
		i++;
		current = current->next;
	}
	cmds->cmd->tab[i] = 0;
	return (0);
}
