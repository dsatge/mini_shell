/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/23 15:13:23 by dsatge           ###   ########.fr       */
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

char	**add_path(char *add, int len, char **path_split)
{
	int		line;
	char	**new;

	line = 0;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
	{
		// clean_to_exit(0, *pipe);
		exit(EXIT_FAILURE);
	}
	while (line < len)
	{
		new[line] = ft_strjoin(path_split[line], add);
		if (!new[line])
		{
			perror("path creation");
			// ft_freetab(new);
			// clean_to_exit(2, *pipe);
		}
		line++;
	}
	ft_freetab(path_split);
	new[line] = 0;
	return (new);
}
//check env with ACCESS
int	init_path(char **env, t_pipe *pipex)
{
	char	*path;
	char	**path_split;
	int		i;
	int		line_path_count;

	path = NULL;
	i = 0;
	if (!env)
		return (-1);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_strtrim(env[i], "PATH=");
	path_split = ft_split(path, ':');
	free(path);
	line_path_count = ft_count_line_split(path_split);
	pipex->path = add_path("/", line_path_count, path_split);
	return (0);
}

int	ft_exec(t_list *cmds, char **env)
{
	pid_t	pid;
	t_pipe	pipex;
	
	init_pipex(cmds, &pipex, env);
	init_path(env, &pipex);
	//GET PATH / ABSOLUT PATH
	if (ft_builtin(cmds, &pipex) == 0)
		return (0);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
	if (pid == 0)
		exe_cmd(cmds, pipex);//CREATE FT
	//FREE pipex.path
	return (0);
}