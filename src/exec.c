/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/22 19:33:17 by dsatge           ###   ########.fr       */
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
	pipex->abs_path = 0;
	(void)cmds;
	// if (cmds->cmd)
	if (env[0] == NULL)
		pipex->abs_path = -1;
	else
		pipex->env = env;
		
}
//check env with ACCESS
int	init_path(char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (!env)
		return (-1);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_strtrim(env[i], "PATH=");
	printf("path = %s\n", path);
	return (0);
}

int	ft_exec(t_list *cmds, char **env)
{
	pid_t	pid;
	t_pipe	pipex;
	
	init_pipex(cmds, &pipex, env);
	init_path(env);
	//GET PATH / ABSOLUT PATH
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
	if (pid == 0)
		exe_cmd(cmds, pipex);//CREATE FT
	return (0);
}