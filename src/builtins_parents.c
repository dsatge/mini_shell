/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parents.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:02:54 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 15:08:40 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	reset_std(t_minish *minish)
{
	if (minish->pipex->redir_in == 1)
	{
		minish->pipex->redir_in = 0;
		dup2(minish->pipex->backup_stdin, STDIN_FILENO);
		close(minish->pipex->backup_stdin);
	}
	if (minish->pipex->redir_out == 1)
	{
		minish->pipex->redir_out = 0;
		dup2(minish->pipex->backup_stdout, STDOUT_FILENO);
		close(minish->pipex->backup_stdout);
	}
	close(minish->pipex->backup_stdin);
	close(minish->pipex->backup_stdout);
}

int	builtins_inparent(t_minish *minish, t_list *cmds, int builtins)
{
	minish->pipex->backup_stdin = dup(STDIN_FILENO);
	minish->pipex->backup_stdout = dup(STDOUT_FILENO);
	if (ft_redir(&cmds, &minish->pipex, minish) == EXIT_FAILURE)
		return (-1);
	if (minish->pipex->redir_out == 1)
	{
		dup2(minish->pipex->outfile_fd, STDOUT_FILENO);
		close(minish->pipex->outfile_fd);
	}
	if (minish->pipex->redir_in == 1)
	{
		dup2(minish->pipex->infile_fd, STDIN_FILENO);
		close(minish->pipex->infile_fd);
	}
	builtins = ft_builtin(&minish->env, minish);
	reset_std(minish);
	return (builtins);
}
