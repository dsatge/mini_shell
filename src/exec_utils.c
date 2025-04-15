/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/15 18:43:31 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_cmd_exe(t_list *cmds, t_pipe *pipex, t_env_head *env_head)
{
	pid_t	pid;
	int		status;

	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		ft_freetab(pipex->path);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), EXIT_FAILURE);
	signal_child();
	if (pid == 0)
	{
		if (ft_redir_manager(cmds, pipex, env_head, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_builtin(cmds, env_head) == 0)
			return (EXIT_SUCCESS);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
			g_error_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

void	firsts_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd,
	t_env_head *env_head)
{
	int		i;
	char	*path_cmd;

	i = 0;
	path_cmd = NULL;
	if (ft_redir_manager(cmds, pipex, env_head, 1) == EXIT_FAILURE)
		return ;
	if (ft_builtin(cmds, env_head) == 0)
		exit(EXIT_SUCCESS);
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0],
			o_cmd->tab, pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
		if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab,
				pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	error_print_msg(o_cmd->tab[0], env_head);
	exit(127);
}

void	last_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd,
	t_env_head *env_head)
{
	int		i;
	char	*path_cmd;

	i = 0;
	path_cmd = NULL;
	if (ft_redir_manager(cmds, pipex, env_head, 0) == EXIT_FAILURE)
		return ;
	if (ft_builtin(cmds, env_head) == 0)
		exit(EXIT_FAILURE);
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0],
			o_cmd->tab, pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
		if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab,
				pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (error_print_msg(o_cmd->tab[0], env_head), exit (127));
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
