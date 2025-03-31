/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/31 13:09:12 by dsatge           ###   ########.fr       */
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

void	first_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
  
  	i = 0;
	path_cmd = NULL;
	printf("FIRST.....\n");
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
		path_cmd = ft_strjoin(pipex->path[i], cmds->o_cmd->tab[0]);
		if (cmds->o_cmd->next != NULL)
			cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->o_cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE FIRST EXE"));
}

void	last_exe(t_list *cmds, t_pipe *pipex)
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
	printf("LAST....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->o_cmd->tab[0]);
		if (cmds->o_cmd->next != NULL)
			cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->o_cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE LAST EXE"));
}

int	ft_redir(t_list **cmds, t_pipe **pipex)
{
	t_list	*list;
	
	list = (*cmds);
	(*pipex)->infile_fd = -1;
	(*pipex)->outfile_fd = -1;
	if (!cmds)
		return (-1);
	printf ("start of the command is : %s~~~~~~\n", list->cmd->tab[0]);
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
		list = list->next;
	}
	if (list && list->cmd->type == pip)
		list = list->next;
	return (0);
}
