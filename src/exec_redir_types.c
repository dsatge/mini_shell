/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:58:49 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/19 17:33:44 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(t_list *list, t_pipe **pipex, t_minish *minish)
{
	if (list->cmd.type == redir && ft_strcmp(list->cmd.tab[0], "<") == 0)
	{
		if (redir_in(pipex, list, minish) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd.type == redir && ft_strcmp(list->cmd.tab[0], "<<") == 0)
	{
		(*pipex)->redir_in = 2;
		if (redir_heredoc(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_redir_out(t_list *list, t_pipe **pipex)
{
	if (list->cmd.type == redir && ft_strcmp(list->cmd.tab[0], ">") == 0)
	{
		if (redir_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd.type == redir && ft_strcmp(list->cmd.tab[0], ">>") == 0)
	{
		if (redir_d_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redir_heredoc(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_in == 1)
		close((*pipex)->infile_fd);
	(*pipex)->fd = open(list->cmd.tab[1], O_RDONLY);
	if ((*pipex)->fd == -1)
	{
		ft_printf(2, "bash: %s: No such file or directory \n", list->cmd.tab[1]);
		unlink(list->cmd.tab[1]);
		close((*pipex)->pipe_fd[0]);
		close((*pipex)->pipe_fd[1]);///clean plus haut???
		return (EXIT_FAILURE);
	}
	(*pipex)->infile_fd = (*pipex)->fd;
	unlink(list->cmd.tab[1]);
	(*pipex)->redir_in = 1;
	return (0);
}
