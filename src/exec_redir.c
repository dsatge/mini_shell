/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:52 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/10 17:09:47 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redir_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_out == 1)
	{
		close((*pipex)->outfile_fd);
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	(*pipex)->redir_out = 1;
	return (0);
}

int redir_d_out(t_pipe **pipex, t_list *list)
{
	if ((*pipex)->redir_out == 1)
	{
		close((*pipex)->outfile_fd);
	}
	(*pipex)->fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*pipex)->fd == -1)
		return (-1);
	(*pipex)->outfile_fd = (*pipex)->fd;
	(*pipex)->redir_out = 1;
	return (0);
}

int	redir_fdin(t_pipe **pipex, t_list *cmds, int prev_pip, t_env_head *env_head)
{
	if ((*pipex)->redir_in == 1)
	{
		dup2((*pipex)->infile_fd, STDIN_FILENO);
		close((*pipex)->infile_fd);
	}
	else if ((*pipex)->redir_in == 2)
	{
		while (cmds)
		{
			if (cmds->cmd->type == redir && ft_strcmp(cmds->cmd->tab[0], "<<") == 0)
			{
				// ft_printf(2, "YO LA TEAM\n");
				heredoc(pipex, cmds, env_head);
			}
			cmds = cmds->next;	
		}
	}
	else if (prev_pip != -1)
	{
		dup2(prev_pip, STDIN_FILENO);
		close(prev_pip);
	}
	return (0);
}

int	redir_fdout(t_pipe **pipex, t_list *cmds)
{
	(void)cmds;
	if ((*pipex)->redir_out == 1)
	{
		dup2((*pipex)->outfile_fd, STDOUT_FILENO);
		close((*pipex)->outfile_fd);
	}
	return (0);
}