/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/17 21:22:48 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cmd(t_list *cmds, t_pipe pipex)
{
	// int i;
	int fd;	
	// i = -1;
	pipex.file = NULL;
	// fd = open()
	(void)fd;
	if (execve(cmds->cmd->tab[0], cmds->cmd->tab, pipex.env) == -1)
		return (perror("ERROR"));
}

void	init_pipex(t_list *cmds, t_pipe *pipex, char **env)
{
	(void)cmds;
	if (cmds->cmd)
	pipex->env = env;
}

int	ft_exec(t_list *cmds, char **env)
{
	pid_t	pid;
	t_pipe	pipex;
	
	init_pipex(cmds, &pipex, env);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
	if (pid == 0)
		exe_cmd(cmds, pipex);//CREATE FT
	return (0);
}