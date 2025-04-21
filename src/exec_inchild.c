/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inchild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 11:39:14 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_manager(t_minish *minish, t_pipe *pipex, t_env_head *env_head, int pip)
{
	t_list	*cmds;
	
	(void)pip;
	cmds = minish->cmds;
	if (ft_redir(&cmds, &pipex, minish) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (minish->pipex->nbr_cmds > 1)
		redir_fdout_pip(&pipex);
	else
		redir_fdout(&pipex, cmds);
	redir_fdin(&pipex, cmds, pipex->prev_pip, env_head);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	return (EXIT_SUCCESS);
}

int	ft_redir(t_list **cmds, t_pipe **pipex, t_minish *minish)
{
	t_list	*list;

	list = (*cmds);
	(*pipex)->redir_in = 0;
	(*pipex)->redir_out = 0;
	if (!cmds)
		return (EXIT_FAILURE);
	while (list && list->cmd.type != pip)
	{
		if (ft_redir_in(list, pipex, minish) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_redir_out(list, pipex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		list = list->next;
	}
	if (list && list->cmd.type == pip)
		list = list->next;
	return (EXIT_SUCCESS);
}
