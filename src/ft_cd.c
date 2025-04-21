/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:14 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/21 11:23:44 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_status(char *path)
{
	unsigned char	exit_code;

	if (chdir(path) == -1)
	{
		ft_printf(2, "bash : cd: %s: %s\n", path, strerror(errno));
		exit_code = 1;
	}
	else
		exit_code = 0;
	return (exit_code);
}

static char	*get_path_no_cmd(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (ft_putstr_fd("cd: HOME undefined\n", 2), NULL);
	return (home);
}

static char	*get_path_yes_cmd(char *path)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (ft_putstr_fd("cd: HOME undefined\n", 2), NULL);
	path = ft_strjoin(home, path + 1);
	if (!path)
		return (ft_putstr_fd("cd: memory allocation error\n", 2), NULL);
	return (path);
}

int	ft_cd(char **cmd)
{
	char	*path;

	if (cmd[1] && cmd[2])
		return (ft_printf(2, "cd: too many arguments\n"), 1);
	if (!cmd[1])
	{
		path = get_path_no_cmd();
		if (path == NULL)
			return (1);
	}
	else
	{
		path = cmd[1];
		if (path[0] == '~')
		{
			path = get_path_yes_cmd(path);
			if (path == NULL)
				return (1);
		}
	}
	g_error_code = exit_status(path);
	return (g_error_code);
}
