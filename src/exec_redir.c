/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/04 15:04:54 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */







# include "minishell.h"

int	redir_in(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_in == 1)
	{
		close((*pipex)->infile_fd);
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
	if ((*pipex)->redir_out == 1)
	{
		close((*pipex)->outfile_fd);
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	// close((*pipex)->fd);
	(*pipex)->redir_out = 1;
	// close((*pipex)->pipe_fd[0]);
	return (0);
}

int	redir_fdin(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
<<<<<<< HEAD

=======
	// printf("redir_pipe value = %i\n", (*pipex)->redir_pipe);
>>>>>>> main
	if ((*pipex)->redir_in == 1)
	{
		dup2((*pipex)->infile_fd, STDIN_FILENO);
		close((*pipex)->infile_fd);
	}
	// else if ((*pipex)->redir_pipe == 1)
	// {
	// 	dup2((*pipex)->pipe_fd[0], STDIN_FILENO);
	// 	close((*pipex)->pipe_fd[0]);
	// }
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
		// close((*pipex)->pipe_fd[0]);
		// printf ("---------------HERE\n");
		dup2((*pipex)->pipe_fd[1], STDOUT_FILENO);
		close((*pipex)->pipe_fd[1]);
<<<<<<< HEAD

=======
>>>>>>> main
	}
	return (0);
}

int	redir_fdout(t_pipe **pipex, t_list *cmds)
{
	(void) cmds;
	if ((*pipex)->redir_out == 1)
	{
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	return (0);
}