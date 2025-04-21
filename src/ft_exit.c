/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/21 15:04:28 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_env_head *env_head, t_minish *minish)
{
	(void)env_head;
	
	ft_printf(2, "Bisous mon chou <3\n");
	if (minish->cmds && minish->cmds->cmd.tab && minish->cmds->cmd.tab[1])
		g_error_code = ft_atoi(minish->cmds->cmd.tab[1]);
	else
		g_error_code = 0;
	if (minish && minish->pipex) 
	{
		close(minish->pipex->backup_stdin);
		close(minish->pipex->backup_stdout);
	}
	free_all(minish, 1);
	exit(g_error_code);
}

