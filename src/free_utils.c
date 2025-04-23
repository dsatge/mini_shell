/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:35:22 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/23 02:14:42 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file_names(t_f_name *files)
{
	t_f_name	*tmp;

	if (!files)
		return ;
	while (files)
	{
		tmp = files->next;
		if (files->f_name)
		{
			free(files->f_name);
			free(files);
		}
		files = tmp;
	}
	return ;
}

void	free_tpipe(t_pipe *pipex)
{
	if (!pipex)
		return ;
	if (pipex->env)
		free_tab(pipex->env);
	if (pipex->path)
		free_tab(pipex->path);
	free(pipex);
	return ;
}

void	free_env(t_env_head *env_head)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env_head->head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->type);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	env_head->head = NULL;
	env_head->size = 0;
}

void	ft_close_all(t_minish *minish)
{
	if (minish->pipex->redir_in != 1)
	{
		close(minish->pipex->infile_fd);
		minish->pipex->redir_in = -1;
	}
	if (minish->pipex->redir_out != 1)
	{
		close(minish->pipex->outfile_fd);
		minish->pipex->redir_out = -1;
	}
	if (minish->pipex->pipe_fd[0] != -1)
	{
		close (minish->pipex->pipe_fd[0]);
		minish->pipex->pipe_fd[0] = -1;
	}
	if (minish->pipex->pipe_fd[1] != -1)
	{
		close (minish->pipex->pipe_fd[1]);
		minish->pipex->pipe_fd[1] = -1;
	}
	if (minish->pipex->prev_pip != -1)
	{
		close(minish->pipex->prev_pip);
		minish->pipex->prev_pip = -1;
	}
}

void	free_all(t_minish *minish, bool clean_env)
{
	if (!minish)
		return ;
	free_list(minish->element_head);
	minish->element_head = NULL;
	minish->head_token = NULL;
	free_tpipe(minish->pipex);
	minish->pipex = NULL;
	free_file_names(minish->f_name);
	minish->f_name = NULL;
	free_cmds(minish->cmds);
	minish->cmds = NULL;
	free_tocmd(minish->o_cmd);
	minish->o_cmd = NULL;
	if (clean_env == true)
	{
		free_env(&minish->env);
		free(minish);
	}
}
