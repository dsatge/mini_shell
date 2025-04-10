/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/10 17:14:45 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	invert_stdin(t_list *cmds, int fd)
{
	printf("CHECK : %s, type = %i\n", cmds->cmd->tab[1], cmds->cmd->type);
	fd = open(cmds->cmd->tab[1], O_RDONLY);
	if (fd == -1)
		return (perror("open failed\n"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

void	first_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd, int prev_pip, t_env_head *env_head)
{
	int i;
	char	*path_cmd;
  
  	i = 0;
	path_cmd = NULL;
	if (ft_redir(&cmds, &pipex) == -1)
	{
		perror("bash: infile: ");
		return;
	}
	redir_fdout_pip(&pipex);
	redir_fdin(&pipex, cmds, prev_pip, env_head);
  	if (ft_builtin(cmds, env_head) == 0)
		exit (EXIT_SUCCESS);
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0], o_cmd->tab, pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
		if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	ft_printf(2, "bash: %s: command not found\n", o_cmd->tab[0]);
	exit(127);
}

void	last_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd, int prev_pip, t_env_head *env_head)
{
	int i;
	char	*path_cmd;
	
	i = 0;
	path_cmd = NULL;
	if (ft_redir(&cmds, &pipex) == EXIT_FAILURE)
	{
		perror("bash: infile: ");
		return ;
	}
	redir_fdout(&pipex, cmds);
	redir_fdin(&pipex, cmds, prev_pip, env_head);
	if (ft_builtin(cmds, env_head) == 0)
		exit (EXIT_FAILURE) ;
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0], o_cmd->tab, pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
    if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (ft_printf(2, "bash: %s: command not found\n", o_cmd->tab[0]), exit (127));
}

int	ft_redir(t_list **cmds, t_pipe **pipex)
{
	t_list	*list;
	
	list = (*cmds);
	(*pipex)->redir_in = 0;
	(*pipex)->redir_out = 0;
	if (!cmds)
		return (EXIT_FAILURE);
	while (list && list->cmd->type != pip)
	{
		if (ft_redir_in(list, pipex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_redir_out(list, pipex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		list = list->next;
	}
	if (list && list->cmd->type == pip)
		list = list->next;
	return (EXIT_SUCCESS);
}

int	ft_redir_in(t_list *list, t_pipe **pipex)
{
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<") == 0)
	{
		if (redir_in(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<<") == 0)
	{
		(*pipex)->redir_in = 2;
	}
	return (EXIT_SUCCESS);
}

int	ft_redir_out(t_list *list, t_pipe **pipex)
{
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">") == 0)
	{
		if (redir_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">>") == 0)
	{
		if (redir_d_out(pipex, list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
