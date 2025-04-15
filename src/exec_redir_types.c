/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:58:49 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/15 16:32:11 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(t_list *list, t_pipe **pipex)
{
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<") == 0)
	{
		if (redir_in(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<<") == 0)
	{
		(*pipex)->redir_in = 2;
	}
	return (EXIT_SUCCESS);
}

int	ft_redir_out(t_list *list, t_pipe **pipex)
{
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">") == 0)
	{
		if (redir_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">>") == 0)
	{
		if (redir_d_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
