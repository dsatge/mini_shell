/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 16:00:11 by dsatge           ###   ########.fr       */
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

void free_tab_2(char **tab, int size)
{
    int i = 0;
    while (i < size)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char **buildtab(t_env_head *env_head)
{
    t_env   *tmp;
    int     i;
    char    **env;
    char    *temp;

    i = 0;
    tmp = env_head->head;
    env = malloc(sizeof(char *) * (env_head->size + 1));
    if (!env)
        return (NULL);
    while (tmp)
    {
        temp = ft_strjoin(tmp->type, "=");
        if (!temp)
            return (free_tab_2(env, i), NULL);
        env[i] = ft_strjoin(temp, tmp->value);
        free(temp);
        if (!env[i])
            return (free_tab_2(env, i), NULL);
        tmp = tmp->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

int	ft_exec(t_list *cmds, t_env_head *env_head)
{
	char **env;
	pid_t	pid;
	t_pipe	pipex;
	t_o_cmd	*o_cmd;
	int		status;
	int		prev_pip;
	
	o_cmd = NULL;
	prev_pip = -1;
	o_cmd = ft_only_cmd(cmds);
	env = buildtab(env_head);
	if (!env)
		return (-1);
	init_pipex(cmds, &pipex, env);
	init_path(env, &pipex);
	// free_tab_2(env, ft_count_line_split(env));
	//GET PATH / ABSOLUT PATH
	while (pipex.nbr_cmds > 1)
	{
		if (pipe(pipex.pipe_fd) == -1)
		{
			perror("pipe");
			ft_freetab(pipex.path);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("ERROR pid firsts\n", 2), 1);//PUT RIGHT EXIT
		if (pid == 0)
		{
			first_exe(cmds, &pipex, o_cmd, prev_pip, env_head);//CREATE FT
		}
		close(pipex.pipe_fd[1]);
		prev_pip = pipex.pipe_fd[0];
		next_cmdexe(&cmds, &o_cmd, &pipex);
	}
	if (pipex.nbr_cmds == 1)
	{
		if (pipe(pipex.pipe_fd) == -1)
		{
			perror("pipe");
			ft_freetab(pipex.path);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("ERROR pid last\n", 2), 1);//PUT RIGHT EXIT
		if (pid == 0)
		{
			last_exe(cmds, &pipex, o_cmd, prev_pip, env_head);//CREATE FT
		}
	}
	// if (pid == 0)
	// 	exit (1);
	waitpid(pid, &status, 0);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	if (prev_pip != -1)	
		close (prev_pip);
	//FREE pipex.path
	return (0);
}
