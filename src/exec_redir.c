/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:52 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/31 18:08:27 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	redir_in(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->infile_fd != -1)
	{
		close((*pipex)->infile_fd);
		(*pipex)->infile_fd = 0;
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_RDONLY);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->infile_fd = (*pipex)->fd;
	(*pipex)->redir_in = 1;
	return (0);
}

int redir_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->outfile_fd != -1)
	{
		close((*pipex)->outfile_fd);
		// close((*pipex)->fd);
		(*pipex)->outfile_fd = 0;
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	(*pipex)->redir_out = 1;
	return (0);
}

int	redir_fdin(t_pipe **pipex, t_list *cmds)
{
	
	(void) cmds;
	if ((*pipex)->redir_in == 1)
	{
		printf("here\n");
		dup2((*pipex)->infile_fd, STDIN_FILENO);
		close((*pipex)->infile_fd);
	}
	else if ((*pipex)->redir_pipe != 0)
	{
		// close((*pipex)->pipe_fd[1]);
		dup2((*pipex)->pipe_fd[0], STDIN_FILENO);//GET bACK CONTENT FROM PIPE
		// close((*pipex)->pipe_fd[1]);
		close((*pipex)->pipe_fd[0]);
	}
	// else
	// 	dup2(STDIN_FILENO, STDIN_FILENO);
	return (0);
}

int	redir_fdout_pip(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
	if ((*pipex)->redir_out == 1)
	{
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
		(*pipex)->redir_pipe = 0;
	}
	else
	{
		close((*pipex)->pipe_fd[0]);
		dup2((*pipex)->pipe_fd[1], STDOUT_FILENO);
		// close((*pipex)->pipe_fd[0]);
		close((*pipex)->pipe_fd[1]);
		(*pipex)->redir_pipe = 1;
	}
	return (0);
}

int	redir_fdout(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
	if ((*pipex)->redir_out != 0)
	{
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	else
	{
		dup2(STDOUT_FILENO, STDOUT_FILENO);
		// close((*pipex)->pipe_fd[0]); ////////THIS ONE CLOSES BECAUSE OF VALGRIND IN ONE EXE
		// close((*pipex)->pipe_fd[1]);
	}
	return (0);
}