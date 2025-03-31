/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:15:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/31 18:44:56 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipex(t_list *cmds, t_pipe *pipex, char **env)
{
	pipex->abs_path = 0;
	pipex->backup_stdin = dup(STDIN_FILENO);
	pipex->backup_stdout = dup(STDOUT_FILENO);
	pipex->redir_in = 0;
	pipex->redir_out = 0;
	pipex->redir_pipe = 0;

	cmds->mem_cmd_nbr = cmds->cmd_nbr;
	(void)cmds;
	if (env[0] == NULL)
	pipex->abs_path = -1;
	else
	pipex->env = env;
}

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
			new_node->tab = ft_calloc(sizeof(char *), ft_count_line_split(list->cmd->tab) + 1);
			if (!new_node->tab)
				return (0);
			while(list->cmd->tab[i] != 0)
			{
				new_node->tab[i] = ft_strdup(list->cmd->tab[i]);
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


// int	cp_cmdtab(t_o_cmd *o_cmd, t_list *list)
// {
// 	int	i;
	
// 	i = 0;
// 	o_cmd->next->tab = ft_calloc(sizeof(char *), ft_count_line_split(list->cmd->tab) + 1);
// 	if (!o_cmd->tab)
// 	return (-1);
// 	while(list->cmd->tab[i] != 0)
// 	{
// 		o_cmd->tab[i] = ft_strdup(list->cmd->tab[i]);
// 		i++;
// 	}
// 	o_cmd->tab[i] = 0;
// 	o_cmd = o_cmd->next;
// 	o_cmd->next = NULL;
// 	return (0);
// }

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

int	next_cmdexe(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex)
{
	if (!cmds)
	return (-1);
	pipex->outfile_fd = -1;
	pipex->redir_in = 0;
	pipex->redir_out = 0;
	(*cmds)->head->cmd_nbr--;
	while (cmds && (*cmds)->cmd->type != pip)
	{
		(*cmds) = (*cmds)->next;
	}
	if (cmds && (*cmds)->cmd->type == pip)
	(*cmds) = (*cmds)->next;
	(*o_cmd) = (*o_cmd)->next;
	return (0);
}

int	ft_exec(t_list *cmds, char **env, t_env *ev)
{
	pid_t	pid;
	t_pipe	pipex;
	t_o_cmd	*o_cmd;
	int		status;
	
	o_cmd = NULL;
	o_cmd = ft_only_cmd(cmds);
	init_pipex(cmds, &pipex, env);
	init_path(env, &pipex);
	//GET PATH / ABSOLUT PATH
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
			first_exe(cmds, &pipex, o_cmd);//CREATE FT
		next_cmdexe(&cmds, &o_cmd, &pipex);
	}
	if (cmds->head->cmd_nbr == 1 && cmds)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("ERROR\n", 2), 1);//PUT RIGHT EXIT
		if (pid == 0)
			last_exe(cmds, &pipex, o_cmd);//CREATE FT
	}
	if (pid == 0)
		exit(1);
	waitpid(pid, &status, 0);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	//FREE pipex.path
	return (0);
}
