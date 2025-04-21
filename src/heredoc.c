/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 14:19:09 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	exit(EXIT_FAILURE);
}

static void	creat_heredoc(t_list *cmds, t_env_head *env_head, char *file_name)
{
	char	*buffer;
	int		fd;

	signal(SIGINT, close_fd);
	signal(SIGQUIT, SIG_IGN);
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer || ft_strcmp(buffer, cmds->cmd.tab[1]) == 0)
		{
			free(buffer);
			break ;
		}
		buffer = ft_expand_heredoc(buffer, env_head);
		ft_putstr_fd(buffer, fd);
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

int	heredoc(t_pipe **pipex, t_list *cmds, t_env_head *env_head, char *file_name)
{
	pid_t	pid_heredoc;
	int		status;
	// t_list	*list;

	(void) pipex;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	// list = cmds;
	pid_heredoc = fork();
	if (pid_heredoc == -1)
	{
		perror("Error fork heredoc");
		return (EXIT_FAILURE);
	}
	if (pid_heredoc == 0)
		creat_heredoc(cmds, env_head, file_name);
	waitpid(pid_heredoc, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (EXIT_FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	// exit_close(pipex, file_name);
	return (EXIT_SUCCESS);
}

static void	file_list(char *name, t_minish *minish)
{
	t_f_name	*new_node;
	t_f_name	*tmp;

	new_node = malloc(sizeof(t_f_name));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->f_name = ft_strdup(name);
	new_node->next = NULL;
	if (!minish->f_name)
		minish->f_name = new_node;
	else
	{
		tmp = minish->f_name;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

char	*file_name(char *eol_file, t_minish *minish)
{
	int i;
	int check_access;
	char *tmp;
	
	i = 0;
	// tmp = ft_strjoin("/tmp/minish_heredoc_", eol_file);
	tmp = ft_strjoin("minish_heredoc_", eol_file);
	if (!tmp)
		return (NULL);
	check_access = access(tmp, F_OK);
	while (check_access == 0)
	{
		tmp = ft_strjoin(tmp, ft_itoa(i));
		if (!tmp)
			return (NULL);
		check_access = access(tmp, F_OK);
		i++;
	}
	file_list(tmp, minish);
	return (tmp);
}

int	heredoc_name(char *name, t_list *cmds)
{
	free(cmds->cmd.tab[1]);
	cmds->cmd.tab[1] = ft_strdup(name);
	if (!cmds->cmd.tab[1])
		return (free(name), EXIT_FAILURE);
	free(name);
	return (EXIT_SUCCESS);
}

int			heredoc_check(t_minish *minish, t_env_head *env_head)
{
	t_list	*head;
	char	*file;

	file = NULL;
	head = minish->cmds;
	while (minish->cmds)
	{
		if (minish->cmds->cmd.type == redir && ft_strcmp(minish->cmds->cmd.tab[0],
			"<<") == 0)
		{
			ft_printf(2, "check cmd %s %s\n", minish->cmds->cmd.tab[0], minish->cmds->cmd.tab[1]);
			file = file_name(minish->cmds->cmd.tab[1], minish);
			if (!file)
				return (EXIT_FAILURE);
			if (heredoc(&minish->pipex, minish->cmds, env_head, file) == EXIT_FAILURE)
			{
				ft_printf(2, "OUUUUUUUUUPS\n");
				g_error_code = 130;
				return (free(file), ft_printf(2 , "\n"), EXIT_FAILURE);
			}
			if (heredoc_name(file, minish->cmds) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		minish->cmds = minish->cmds->next;
	}
	minish->cmds = head;
	return (EXIT_SUCCESS);
}

//enregistrer tableau liste chainee des file a unlink.