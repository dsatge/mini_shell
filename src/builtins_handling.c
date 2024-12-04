/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2024/12/04 17:37:44 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin(t_token *cmd)
{
	if (ft_strcmp(cmd->str, "echo") == 0)
		return(ft_echo(cmd), 0);
	// else if (ft_strcmp(cmd->str, "cd") == 0)
	// 	return(ft_cd(cmd->str), 0);
	else if (ft_strcmp(cmd->str, "exit") == 0)
		return(ft_exit(cmd), 0);
	// else if (ft_strcmp(cmd->str, "env") == 0)
	// 	return(ft_env(cmd->str), 0);
	// else if (ft_strcmp(cmd->str, "unset") == 0)
	// 	return(ft_unset(cmd->str), 0);
	// else if (ft_strcmp(cmd->str, "export") == 0)
	// 	return(ft_export(cmd->str), 0);
	else if (ft_strcmp(cmd->str, "pwd") == 0)
		return(ft_pwd(cmd), 0);
	return (1);
}