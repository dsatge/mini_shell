/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2025/01/23 15:21:41 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_list *cmds, t_pipe *pipex)
{
	(void)pipex;
	if (!cmds && !cmds->cmd && !cmds->cmd->tab)
		return (1);
	if (ft_strcmp(cmds->cmd->tab[0], "echo") == 0)
		return(ft_echo(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "cd") == 0)
		return(ft_cd(cmds->cmd->tab), 0);
	// else if (ft_strcmp(cmd->str, "unset") == 0)
	// 	return(ft_unset(cmd), 0);
	// else if (ft_strcmp(cmd->str, "exit") == 0)
	// 	return(ft_exit(cmd), 0);
	// else if (ft_strcmp(cmd->str, "env") == 0)
	// 	return(ft_env(cmd->str), 0);
	// else if (ft_strcmp(cmd->str, "export") == 0)
	// 	return(ft_export(cmd->str), 0);
	// else if (ft_strcmp(cmds->cmd->tab[0], "pwd") == 0)
	// 	return(ft_pwd(cmds->cmd->tab), 0);
	return (1);
}