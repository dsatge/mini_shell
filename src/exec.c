/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/11 17:02:49 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_o_cmd	*ft_only_cmd(t_list *cmds)
{
	t_list	*list;
	t_o_cmd	*head;
	t_o_cmd	*current;
	t_o_cmd	*new_node;
	int		i;

	list = cmds;
	head = NULL;
	current = NULL;
	i = 0;
	if (!list || !list->cmd || !list->cmd->tab[0])
		return (NULL);
	while (list)
	{
		i = 0;
		if (list->cmd->type == word)
		{
			new_node = malloc(sizeof(t_o_cmd));
			if (!new_node)
				return (NULL);
			new_node->tab = ft_calloc(sizeof(char *),
					ft_count_line_split(list->cmd->tab) + 1);
			if (!new_node->tab)
				return (0);
			while (list->cmd->tab[i] != 0)
			{
				new_node->tab[i] = ft_strdup(list->cmd->tab[i]);
				if (!new_node->tab[i])
					return (NULL);
				i++;
			}
			new_node->tab[i] = 0;
			new_node->next = NULL;
			if (head == NULL)
				head = new_node;
			else
				current->next = new_node;
			current = new_node;
		}
		list = list->next;
	}
	return (head);
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
			return (NULL);
			// ft_freetab(new);
			// clean_to_exit(2, *pipe);
		}
		line++;
	}
	ft_freetab(path_split);
	new[line] = 0;
	return (new);
}
// check env with ACCESS
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
		ft_printf(2, "bash: (INSERER COMMANDE): No such file or directory\n");
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

int	ft_exec(t_list *cmds, t_env_head *env_head)
{
	char	**env;
	// pid_t	pid;
	t_pipe	pipex;
	t_o_cmd	*o_cmd;
	// int		status;
	int		prev_pip;
  
	o_cmd = NULL;
	prev_pip = -1;
	o_cmd = ft_only_cmd(cmds);
	env = buildtab(env_head);
	if (!env)
		return (-1);
	init_pipex(cmds, &pipex, env);
	init_path(env, &pipex);
	if (pipex.nbr_cmds == 1)
	{
		if (ft_builtin(cmds, env_head) == 0)
			return (0); 
	}
	if (exec_multiple_cmds(&cmds, &o_cmd, &pipex, &prev_pip, env_head) != 0)
		return (1);
	if (pipex.nbr_cmds == 1 || pipex.nbr_cmds == 0)
	{
		if (ft_builtin(cmds, env_head) == 0)
			return (0);
		return (exec_single_cmd(cmds, &pipex, o_cmd, prev_pip, env_head));
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	ft_freetab(env);
	if (prev_pip != -1)	
		close (prev_pip);
	return (0);
}
