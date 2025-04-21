/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/21 11:14:12 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_env_head *env_head, t_minish *minish)
{
	if (!minish->cmds && !minish->cmds->cmd.tab)
		return (1);
	ft_expand_args(minish->cmds, env_head);
	if (ft_strcmp(minish->cmds->cmd.tab[0], "exit") == 0)
		return (ft_exit(env_head, minish), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "echo") == 0)
		return (ft_echo(minish->cmds->cmd.tab), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "cd") == 0)
		return (ft_cd(minish->cmds->cmd.tab), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "pwd") == 0)
		return (ft_pwd(minish->cmds->cmd.tab), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "env") == 0)
		return (ft_env(env_head), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "unset") == 0)
		return (ft_unset(minish->cmds->cmd.tab, env_head), 0);
	else if (ft_strcmp(minish->cmds->cmd.tab[0], "export") == 0)
		return (ft_export(minish->cmds->cmd.tab, env_head), 0);
	return (1);
}
