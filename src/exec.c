/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 03:44:19 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_path(char *add, int len, char **path_split)
{
	int		line;
	char	**new;

	line = 0;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
	{
		ft_freetab(path_split);
		exit(EXIT_FAILURE);
	}
	while (line < len)
	{
		new[line] = ft_strjoin(path_split[line], add);
		if (!new[line])
		{
			perror("path creation");
			ft_freetab(new);
			return (NULL);
		}
		line++;
	}
	ft_freetab(path_split);
	new[line] = 0;
	return (new);
}

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
	if (!env[i])
	{
		pipex->abs_path = 1;
		return (1);
	}
	path = ft_strtrim(env[i], "PATH=");
	path_split = ft_split(path, ':');
	if (!path_split)
		return (1);
	free(path);
	line_path_count = ft_count_line_split(path_split);
	pipex->path = add_path("/", line_path_count, path_split);
	return (0);
}

static void	close_clean(t_pipe *pipex, int prev_pip, char **env)
{
	(void)env;
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (prev_pip >= 0)
		close(prev_pip);
	return ;
}

int	ft_exec(t_list *cmds, t_env_head *env_head, t_minish *minish)
{
	char	**env;
	int		builtins;

	builtins = 0;
	minish->o_cmd = ft_only_cmd(cmds);
	env = buildtab(env_head);
	if (!env)
		return (-1);
	init_pipex(cmds, minish->pipex, env);
	init_path(env, minish->pipex);
	if (heredoc_check(minish, env_head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (minish->pipex->nbr_cmds <= 1)
	{
		builtins = builtins_inparent(minish, cmds, builtins);
		if (builtins == 0)
			return (0);
		if (builtins == -1)
			return (EXIT_FAILURE);
	}
	if (exec_cmds(&minish->o_cmd, minish, env_head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_clean(minish->pipex, minish->pipex->prev_pip, env);
	return (0);
}
