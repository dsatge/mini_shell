/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:41:42 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/22 04:08:40 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_slash_dot(char *buffer)
{
	int	i;
	int	flag;

	i = 0;
	if (!buffer || !buffer[0])
		return (0);
	while (buffer[i] == 32 || buffer[i] == '\t')
		i++;
	flag = 1;
	while (buffer[i])
	{
		if (buffer[i] != '/' && buffer[i] != '.')
			flag = 0;
		i++;
	}
	if (flag)
	{
		ft_printf(2, "bash: %s: No such file or directory\n", buffer);
		return (1);
	}
	return (0);
}

int	error_special(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	if (is_only_slash_dot(buffer) == 1)
	{
		g_error_code = 1;
		return (1);
	}
	while (buffer[i])
	{
		while (buffer[i] == 32 || buffer[i] == '\t')
			i++;
		if (ft_strcmp(buffer, ":") == 0 || ft_strcmp(buffer, "#") == 0)
			return (1);
		if (ft_strcmp(buffer, "!") == 0)
		{
			g_error_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	error_print_msg(char *str, t_env_head *env_head)
{
	char	*cpy_str;

	cpy_str = ft_strdup(str);
	if (!cpy_str)
	{
		perror("Error: malloc");
		return ;
	}
	cpy_str = ft_expand_heredoc(cpy_str, env_head);
	ft_printf(2, "bash: %s: command not found\n", cpy_str);
	free(cpy_str);
	return ;
}
