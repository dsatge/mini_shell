/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:52 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/28 18:37:36 by dsatge           ###   ########.fr       */
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
	return (0);
}

int redir_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->outfile_fd != -1)
	{
		close((*pipex)->outfile_fd);
		close((*pipex)->fd);
		(*pipex)->outfile_fd = 0;
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	return (0);
}

int	redir_fdin(t_pipe **pipex, t_list *cmds)
{
	
	(void) cmds;
	if ((*pipex)->infile_fd != -1)
	{
		dup2((*pipex)->infile_fd, STDIN_FILENO);
		close((*pipex)->infile_fd);
	}
	else if ((*pipex)->pipe_fd[1] != (*pipex)->mempipe_fd1)
	{
		printf("~~~~~~~~~~~~~LETS CHECK pipe_fd[1] = %d and meme = %d\n", (*pipex)->pipe_fd[1], (*pipex)->mempipe_fd1);
		close((*pipex)->pipe_fd[1]);
		dup2((*pipex)->pipe_fd[0], STDIN_FILENO);//GET bACK CONTENT FROM PIPE
		// close((*pipex)->pipe_fd[1]);
		close((*pipex)->pipe_fd[0]);
	}
	return (0);
}

int	redir_fdout_pip(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
	if ((*pipex)->outfile_fd != -1)
	{
		printf("Only if redir??\n");
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	else
	{
		printf("check pipe %d mem = %d\n", (*pipex)->pipe_fd[0], (*pipex)->mempipe_fd0);
		close((*pipex)->pipe_fd[0]);
		printf("Rdir to pipe incoming\n");
		dup2((*pipex)->pipe_fd[1], STDOUT_FILENO);
		// close((*pipex)->pipe_fd[0]);
		close((*pipex)->pipe_fd[1]);
	}
	return (0);
}

int	redir_fdout(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
	if ((*pipex)->outfile_fd != -1)
	{
		printf("STDOUT changed\n");
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	else
	{
		printf("STDOUT not changed\n");
		dup2(STDOUT_FILENO, STDOUT_FILENO);
		// close((*pipex)->pipe_fd[0]); ////////THIS ONE CLOSES BECAUSE OF VALGRIND IN ONE EXE
		// close((*pipex)->pipe_fd[1]);
	}
	return (0);
}