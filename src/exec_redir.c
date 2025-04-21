/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:52 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 16:53:20 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(t_pipe **pipex, t_list *list, t_minish *minish)
{
	(void)minish;
	
	if ((*pipex)->redir_in == 1)
		close((*pipex)->infile_fd);
	(*pipex)->fd = open(list->cmd.tab[1], O_RDONLY);
	//if redirpipe = 1 on peut aller chercher dans pipe
	if ((*pipex)->fd == -1)
	{
		ft_printf(2, "bash: %s: No such file or directory \n", list->cmd.tab[1]);
		close((*pipex)->pipe_fd[0]);
		close((*pipex)->pipe_fd[1]);
		free_list(minish->element_head);
		minish->element_head = NULL;
		minish->head_token = NULL;
		return (EXIT_FAILURE);
	}
	(*pipex)->infile_fd = (*pipex)->fd;
	(*pipex)->redir_in = 1;
	return (0);
}

int	redir_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_out == 1)
	{
		close((*pipex)->outfile_fd);
	}
	(*pipex)->fd = open(list->cmd.tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	(*pipex)->redir_out = 1;
	return (0);
}

int	redir_d_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_out == 1)
	{
		close((*pipex)->outfile_fd);
	}
	(*pipex)->fd = open(list->cmd.tab[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	(*pipex)->redir_out = 1;
	return (0);
}

