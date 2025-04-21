/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:35:50 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 19:18:39 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	free_file_names(t_f_name *files)
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

void	free_all_heredoc(t_minish *minish, bool clean_env)
{
    if (!minish)
		return ;
	free_list(minish->element_head);
	minish->element_head = NULL;
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