/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:35:50 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/21 23:34:50 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
