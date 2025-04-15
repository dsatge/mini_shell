/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/15 17:07:32 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_list *cmds, t_env_head *env_head, char **envp)
{
	if (!cmds && !cmds->cmd && !cmds->cmd->tab)
		return (1);
	ft_expand_args(cmds, env_head);
	if (ft_strcmp(cmds->cmd->tab[0], "exit") == 0)
		return (ft_exit(cmds, env_head, envp), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "echo") == 0)
		return (ft_echo(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "cd") == 0)
		return (ft_cd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "pwd") == 0)
		return (ft_pwd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "env") == 0)
		return (ft_env(env_head), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "unset") == 0)
		return (ft_unset(cmds->cmd->tab, env_head), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "export") == 0)
		return (ft_export(cmds->cmd->tab, env_head), 0);
	return (1);
}
