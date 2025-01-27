/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/27 18:03:25 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	one_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	// dup2(pipex->pipe_fd[1], STDIN_FILENO);
	// dup2(pipex->pipe_fd[0], STDOUT_FILENO);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("ONE\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	first_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	// dup2(pipex->pipe_fd[1], STDIN_FILENO);
	// dup2(pipex->pipe_fd[0], STDOUT_FILENO);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("FIRST\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	next_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	// dup2(pipex->pipe_fd[1], STDIN_FILENO);
	// dup2(pipex->pipe_fd[0], STDOUT_FILENO);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("FOLLOWERS....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	last_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	// dup2(pipex->pipe_fd[1], STDIN_FILENO);
	// dup2(pipex->pipe_fd[0], STDOUT_FILENO);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("LAST....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}
