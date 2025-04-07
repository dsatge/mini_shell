/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/07 19:27:38 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	// ft_printf(2, "\n");
	exit(EXIT_FAILURE);
}

static void creat_heredoc(t_pipe **pipex, t_list *cmds, t_o_cmd *o_cmd)
{
    char	*buffer;
	char	*path_cmd;
    // int fd;
	int	i;

	i = 0;
	path_cmd = NULL;
    (*pipex)->infile_fd = open("File_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if ((*pipex)->infile_fd == -1)
        return ;
    while (1)
    {
        buffer = readline("heredoc> ");
        if (!buffer)
        {
            ft_putstr_fd("close heredoc\n", 2);
            close((*pipex)->infile_fd);
            unlink("File_heredoc");
            return ;
        }
        if (!ft_strcmp(buffer, cmds->cmd->tab[1]))
        {
			dup2((*pipex)->infile_fd, STDIN_FILENO);
			close((*pipex)->infile_fd);
			free(buffer);
            break;
        }
        ft_putstr_fd(buffer, (*pipex)->infile_fd);
        write((*pipex)->infile_fd, "\n", 1);
        free(buffer);
    }
	while ((*pipex)->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin((*pipex)->path[i], o_cmd->tab[0]);
		// if (cmds->o_cmd->next != NULL)
		// 	cmds->o_cmd = cmds->o_cmd->next;
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, o_cmd->tab, (*pipex)->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
}

int heredoc(t_pipe **pipex, t_list *cmds, t_o_cmd *o_cmd)
{
    int pid;
    int status;
    
	ft_printf(2, "cmds = %s, o_cmd = %s\n", cmds->cmd->tab[1], o_cmd->tab[0]);
	signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
	{
		perror("Error fork heredoc");
		return (EXIT_FAILURE);
	}
    if (pid == 0)
    {
        signal(SIGINT, close_fd);
        creat_heredoc(pipex, cmds, o_cmd);
        // exit(EXIT_SUCCESS);
    }
    wait(&status);
	unlink("File_heredoc");
    signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handle);
    return (EXIT_SUCCESS);
}
