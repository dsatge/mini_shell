/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:09:29 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/10 17:09:50 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_fdout_pip(t_pipe **pipex)
{
	if ((*pipex)->redir_out == 1)
	{
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	else
	{
		close((*pipex)->pipe_fd[0]);
		dup2((*pipex)->pipe_fd[1], STDOUT_FILENO);
		close((*pipex)->pipe_fd[1]);
	}
	return (0);
}