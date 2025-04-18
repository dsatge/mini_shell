/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/18 16:42:41 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_file(t_pipe *pipex, t_o_cmd *o_cmd, t_minish *minish)
{
	if (ft_strchr(o_cmd->tab[0], '/'))
	{
		if (access(o_cmd->tab[0], F_OK) != 0)
			return (ft_printf(2, "bash: %s: No such file or directory\n",
				o_cmd->tab[0]), free_all(minish, 1), exit(127), EXIT_FAILURE);
		else if (access(o_cmd->tab[0], X_OK) != 0)
			return (ft_printf(2, "bash: %s: Permission denied\n",
				o_cmd->tab[0]), free_all(minish, 1), exit(126), EXIT_FAILURE);
		else if (execve(o_cmd->tab[0], o_cmd->tab, pipex->env) == -1)
			return (perror("execve"), free_all(minish, 1), exit(1), EXIT_FAILURE);
	}		
	return (EXIT_SUCCESS);
}

int	no_cmd_exe(t_list *cmds, t_minish *minish, t_env_head *env_head)
{
	pid_t	pid;
	int		status;
	(void)cmds;

	if (pipe(minish->pipex->pipe_fd) == -1)
	{
		perror("pipe");
		free_all(minish, 1);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), EXIT_FAILURE);
	signal_child();
	if (pid == 0)
	{
		if (ft_redir_manager(minish, minish->pipex, env_head, 0) == EXIT_FAILURE)
			return (free_all(minish, 1), exit(1), EXIT_FAILURE);
		if (ft_builtin(env_head, minish) == 0)
			return (EXIT_SUCCESS);
		free_all(minish, 1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

void	firsts_exe(t_list *cmds, t_minish *minish, t_o_cmd *o_cmd,
	t_env_head *env_head)
{
	int		i;
	char	*path_cmd;
	(void)  cmds;

	i = 0;
	path_cmd = NULL;
	if (ft_redir_manager(minish, minish->pipex, env_head, 1) == EXIT_FAILURE)
		return (free_all(minish, 1), exit(EXIT_FAILURE));
	if (ft_builtin(env_head, minish) == 0)
		exit(EXIT_SUCCESS);
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0],
			o_cmd->tab, minish->pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
 	check_file(minish->pipex, o_cmd, minish);
	while (minish->pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(minish->pipex->path[i], o_cmd->tab[0]);
		if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab,
				minish->pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	error_print_msg(o_cmd->tab[0], env_head);
	ft_printf(2, "[FIRST CHILD]something wrong\n");
	free_all(minish, 1);
	exit(127);
}

void	last_exe(t_list *cmds, t_minish *minish, t_o_cmd *o_cmd,
	t_env_head *env_head)
{
	int		i;
	char	*path_cmd;
	(void)cmds;

	i = 0;
	path_cmd = NULL;
	if (ft_redir_manager(minish, minish->pipex, env_head, 0) == EXIT_FAILURE)
		return (free_all(minish, 1), exit(EXIT_FAILURE));
	if (ft_builtin(env_head, minish) == 0)
		exit(EXIT_FAILURE);
	if (access(o_cmd->tab[0], F_OK | X_OK) == 0 && execve(o_cmd->tab[0],
			o_cmd->tab, minish->pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
	check_file(minish->pipex, o_cmd, minish);
	while (minish->pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(minish->pipex->path[i], o_cmd->tab[0]);
		if (!path_cmd)
			return (perror("strjoin failed"), exit(1));
		printf("PATH_CMD: %s\n", path_cmd);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab,
				minish->pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	// TO DELETE ***********************
	ft_printf(2, "[LAST CHILD]something wrong\n");
	return (error_print_msg(o_cmd->tab[0], env_head), free_all(minish, 1), exit(127));
}

