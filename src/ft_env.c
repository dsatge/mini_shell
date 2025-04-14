/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:16 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/14 19:42:23 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type_env(char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	res = ft_calloc(sizeof(char), i + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, cmd, i);
	res[i] = '\0';
	return (res);
}

char	*get_value_env(char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '\0')
		return (ft_strdup(""));
	i++;
	res = ft_calloc(sizeof(char), (ft_strlen(cmd) - i) + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, &cmd[i], ft_strlen(cmd) - i);
	return (res);
}

int	ft_init_env(char **env, t_env_head *env_head)
{
	int		i;
	t_env	*tmp;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (ft_putstr_fd("Error malloc env in ft_init_env\n", 2), -1);
		new->type = get_type_env(env[i]);
		if (!new->type)
			return (ft_putstr_fd("Error malloc value in ft_init_env\n", 2), -1);
		new->value = get_value_env(env[i]);
		if (!new->value)
			return (ft_putstr_fd("Error malloc value in ft_init_env\n", 2), -1);
		i++;
		tmp = env_head->head;
		env_head->head = new;
		env_head->head->next = tmp;
		env_head->size++;
	}
	return (0);
}

void	ft_env(t_env_head *env_head)
{
	t_env	*tmp;

	if (!env_head->head || !env_head->head->type)
		return ;
	tmp = env_head->head;
	while (tmp->next)
	{
		ft_printf(2, "%s=", tmp->type);
		ft_printf(2, "%s\n", tmp->value);
		tmp = tmp->next;
	}
	ft_printf(2, "%s=", tmp->type);
	ft_printf(2, "%s\n", tmp->value);
	g_error_code = 0;
}
