/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:51:54 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 17:23:28 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds(t_list *cmd_list)
{
	t_list	*current;
	int		cmds;

	if (!cmd_list)
		return (-1);
	cmds = 0;
	current = cmd_list;
	while (current)
	{
		if (current->cmd.type == word)
			cmds++;
		current = current->next;
	}
	return (cmds);
}

void	init_pipex(t_list *cmds, t_pipe *pipex, char **env)
{
	(void)cmds;
	pipex->abs_path = 0;
	pipex->prev_pip = -1;
	pipex->redir_in = 0;
	pipex->redir_out = 0;
	pipex->redir_pipe = 0;
	pipex->env = env;
}

int	next_cmdexe(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex)
{
	if (!cmds)
		return (-1);
	pipex->nbr_cmds--;
	while (cmds && (*cmds)->cmd.type != pip && (*cmds)->next)
	{
		(*cmds) = (*cmds)->next;
	}
	if (cmds && (*cmds)->cmd.type == pip)
		(*cmds) = (*cmds)->next;
	if ((*o_cmd)->next != NULL)
		(*o_cmd) = (*o_cmd)->next;
	return (0);
}
