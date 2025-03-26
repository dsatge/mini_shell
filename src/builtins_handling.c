/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2025/03/26 17:07:37 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_list *cmds, t_pipe *pipex, t_env *ev)
{
	(void)pipex;
	if (!cmds && !cmds->cmd && !cmds->cmd->tab)
		return (1);
	if (ft_strcmp(cmds->cmd->tab[0], "echo") == 0)
		return(ft_echo(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "cd") == 0)
		return(ft_cd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "pwd") == 0)
		return(ft_pwd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "env") == 0)
		return(ft_env(ev), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "unset") == 0)
		return(ft_unset(cmds->cmd->tab, ev), 0);
	// else if (ft_strcmp(cmds->cmd->tab[0], "<<") == 0)
	// 	return(heredoc(cmds), 0);
	// else if (ft_strcmp(cmd->str, "export") == 0)
	// 	return(ft_export(cmd->str), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "exit") == 0)
		return(ft_exit(cmds), 0);
	return (1);
}
