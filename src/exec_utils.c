/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/21 17:38:24 by dsatge           ###   ########.fr       */
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

void	one_exe(t_list *cmds, t_pipe *pipex)
{
	/*MISSING:
	-securities*/
	int i;
	char	*path_cmd;
	int fd;	

	i = 0;
	path_cmd = NULL;
	fd = 0;
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	if (pipex->outfile_fd != -1)
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	while (cmds && cmds->cmd->type != word)
		cmds = cmds->next;
	printf("ONE CMD\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			if (execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
				return (exit(127), perror("exe_cmd:"));
		}
		i++;
	}
	return (perror("127"));
}

void	first_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	
	i = 0;
	path_cmd = NULL;
	//close pipe_fd?
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	else
		dup2(pipex->pipe_fd[0], STDIN_FILENO);//GET bACK CONTENT FROM PIPE
	if (pipex->outfile_fd != -1)
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	else
		{
			dup2(pipex->pipe_fd[1], STDOUT_FILENO);
			close(pipex->pipe_fd[1]);
			close(pipex->pipe_fd[0]);
		}
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

void	last_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		printf("Redirection de file vers STDIN, fd = %d (fichier: %s)\n", 
			pipex->infile_fd, cmds->cmd->tab[1]);  // Vérifie bien le fichier ici
		if (fcntl(pipex->infile_fd, F_GETFD) == -1)
			printf("🚨 ERREUR: infile_fd est déjà fermé !\n");
		else
	 	{
			dup2(pipex->infile_fd, STDIN_FILENO);
			printf("✅ infile_fd est bien ouvert, on l'assigne !\n");
			close(pipex->infile_fd);
		}
	}
	else if(cmds->mem_cmd_nbr == 0)
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);//GET bACK CONTENT FROM PIPE
		close(pipex->pipe_fd[1]);
		close(pipex->pipe_fd[0]);
	}
	if (pipex->outfile_fd != -1)
	{
		printf("Redirection de file vers STDOUT, fd = %d\n", pipex->outfile_fd);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	printf("LAST....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->o_cmd->tab[0]);
		if (cmds->o_cmd->next != NULL)
			cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}
///HERE : issue with redir, alway takes the first redir instead of the last one. 
int	ft_redir(t_list *cmds, t_pipe *pipex)
{
	t_list	*list;
	int		fd;

	list = cmds;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	if (!list)
		return (-1);
	while (list && list->cmd->type != pip)
	{
		printf("list = %s\n", list->cmd->tab[1]);
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<") == 0)
		{
			if (pipex->infile_fd != -1)
			{
				close(pipex->infile_fd);
				pipex->infile_fd = -1;
			}
			fd = open(list->cmd->tab[1], O_RDONLY);
			if (fd == -1)
			return (-1);
			pipex->infile_fd = fd;
			cmds = cmds->next;
		}
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">") == 0)
		{
			if (pipex->outfile_fd != 1)
			{
				close(pipex->outfile_fd);
				pipex->outfile_fd = 0;
			}
			fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			pipex->outfile_fd = fd;
			cmds = cmds->next;
		}
		list = list->next;
	}
	return (0);
}
