/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/21 16:20:19 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipex(t_list *cmds, t_pipe *pipex, char **env)
{
	pipex->abs_path = 0;
	ft_only_cmd(cmds);
	printf("CHECK HEAD OF CMD %s\n", cmds->o_cmd->tab[0]);
	cmds->mem_cmd_nbr = cmds->cmd_nbr;
	(void)cmds;
	// if (cmds->cmd)
	if (env[0] == NULL)
		pipex->abs_path = -1;
	else
		pipex->env = env;
		
}

int	ft_only_cmd(t_list *cmds)
{
	t_list	*list;
	t_o_cmd	*head;
	
	int		i;

	list = cmds;
	i = 0;
	if (!cmds || !cmds->cmd || !cmds->cmd->tab[0])
		return (-1);
	cmds->o_cmd = malloc(sizeof(t_o_cmd));
	head = cmds->o_cmd;
	if (!cmds->o_cmd)
		return (-1);
	while (list)
	{
		if (list->cmd->type == word)
		{
			cmds->o_cmd->tab = ft_calloc(sizeof(char *), ft_count_line_split(list->cmd->tab) + 1);
			if (!cmds->o_cmd->tab)
				return (-1);
			while(list->cmd->tab[i] != 0)
			{
				cmds->o_cmd->tab[i] = ft_strdup(list->cmd->tab[i]);
				i++;
			}
			cmds->o_cmd->tab[i] = 0;
			cmds->o_cmd->next = NULL;
		}
		list = list->next;
	}
	while (list)
	{
		if (list->cmd->type == word)
			cp_cmdtab(cmds, list); //FILL TAB
		list = list->next;
	}
	cmds->o_cmd = head;
	return (0);
}

int	cp_cmdtab(t_list *cmds, t_list *list)
{
	int	i;
	
	i = 0;
	cmds->o_cmd->next->tab = ft_calloc(sizeof(char *), ft_count_line_split(list->cmd->tab) + 1);
	if (!cmds->o_cmd->tab)
		return (-1);
	while(list->cmd->tab[i] != 0)
	{
		cmds->o_cmd->tab[i] = ft_strdup(list->cmd->tab[i]);
		i++;
	}
	cmds->o_cmd->tab[i] = 0;
	cmds->o_cmd = cmds->o_cmd->next;
	cmds->o_cmd->next = NULL;
	return (0);
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

int	ft_exec(t_list *cmds, char **env, t_env *ev)
{
	pid_t	pid;
	t_pipe	pipex;
	int		status;
	
	init_pipex(cmds, &pipex, env);
	init_path(env, &pipex);
	//GET PATH / ABSOLUT PATH
	printf("cmds = %i\n", cmds->head->cmd_nbr);
	if (ft_builtin(cmds, &pipex, ev) == 0)
		return (0);
	if (pipe(pipex.pipe_fd) == -1)
	{
		perror("pipe");
		ft_freetab(pipex.path);
		exit(EXIT_FAILURE);
	}
	while (cmds->head->cmd_nbr > 1)
	{
		pid = fork();
		if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
		if (pid == 0)
		{
			first_exe(cmds, &pipex);//CREATE FT
		}
		cmds->head->cmd_nbr--;
		cmds = cmds->next;
	}
	// while (cmds->head->cmd_nbr > 1 && cmds && cmds->next)
	// {
		// 	cmds = cmds->next;
		// 	pid = fork();
		// 	if (pid == -1)
		// 		return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
		// 	if (pid == 0)
		// 	{
			// 		next_exe(cmds, &pipex);//CREATE FT
			// 	}
			// cmds->head->cmd_nbr--;
			// }
	if (cmds->head->cmd_nbr == 1 && cmds)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
		if (pid == 0)
		{
			last_exe(cmds, &pipex);//CREATE FT
		}
		cmds->head->cmd_nbr--;
	}
	if (pid == 0)
		exit(1);
	// wait(&pid);
	waitpid(pid, &status, 0);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	//FREE pipex.path
	return (0);
}
