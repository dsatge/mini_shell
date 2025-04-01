/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/01 18:53:29 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// static int redir_heredoc()
// {
//     int fd;

//     fd = open("File_heredoc", O_RDONLY);
//     if (fd == -1)
//         return (perror("open heredoc failed"), -1);
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         close(fd);
//         return (perror("dup2 failed"), -1);
//     }
//     close(fd);
//     return (0);
// }

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

void	first_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd)
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
	redir_fdin(&pipex, cmds);
	redir_fdout_pip(&pipex, cmds); /// NE PAS OUBLIER DE DECOMMENTER QUAND PATH FONCTIONNE !!!
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
		// if (cmds->o_cmd->next != NULL)
		// 	cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab, pipex->env) == -1)
		return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE FIRST EXE"));
}

void	last_exe(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd)
{
	int i;
	char	*path_cmd;
	
	i = 0;
	path_cmd = NULL;
	if (ft_redir(&cmds, &pipex) == -1)
	{
		perror("bash: infile: ");
		return ;
	}
	redir_fdin(&pipex, cmds);
	redir_fdout(&pipex, cmds);
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], o_cmd->tab[0]);
    if (path_cmd == NULL)
		  return (perror("strjoin failed"), exit(1));
		// if (o_cmd->next != NULL)
		// 	cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE LAST EXE"));
}

int	ft_redir(t_list **cmds, t_pipe **pipex)
{
	t_list	*list;
	char	*buff;
	
	list = (*cmds);
	buff = NULL;
	(*pipex)->redir_in = 0;
	(*pipex)->redir_out = 0;
	if (!cmds)
		return (-1);
	while (list && list->cmd->type != pip)
	{
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<") == 0)
		{
			if (redir_in(pipex, list) == -1)
				return (-1);
		}
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">") == 0)
		{
			if (redir_out(pipex, list) == -1)
				return (-1);
		}
		// if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<<") == 0)
		// {
    	// 	if (heredoc(*cmds) == -1)
	    // 	    return (-1);
    	// 	if (redir_heredoc() == -1)
        // 		return (-1);
		// }
		list = list->next;
	}
	printf("~~~~~~~~~~~\n");
	if ((*pipex)->redir_in == 0)
	{
		int reader = 0;
		ioctl((*pipex)->pipe_fd[0], FIONREAD, &reader);	
		if (reader > 0)
			printf("VICTORRRRRRYYYYYYYYYYYYYYYYYYYY\n");
		else
			printf("fuck you \n");

		if (reader != 0)
		{
			close((*pipex)->pipe_fd[1]);
			printf("INSIDE IF\n");
			(*pipex)->redir_pipe = 1;
			free(buff);
		}
		else
		{
			printf("INSIDE ELSE\n");			
			close((*pipex)->pipe_fd[1]);
			close((*pipex)->pipe_fd[0]);
		}
	}
	if (list && list->cmd->type == pip)
		list = list->next;
	return (0);
}
