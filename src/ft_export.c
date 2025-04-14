/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:19 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/14 19:42:35 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_value_env(t_env *current, char *cmd)
{
	if (current->value)
		free(current->value);
	current->value = get_value_env(cmd);
	if (!current->value)
		return (-1);
	return (0);
}

static void	creation(t_env_head *env_head, char *cmd, char *type)
{
	t_env	*current;
	t_env	*new_env;

	current = env_head->head;
	while (current)
	{
		if (current->type && ft_strcmp(current->type, type) == 0)
		{
			set_value_env(current, cmd);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return ;
	new_env->type = ft_strdup(type);
	if (!new_env->type)
		return (free(new_env));
	set_value_env(new_env, cmd);
	current->next = new_env;
	env_head->size++;
}

int	ft_export(char **cmd, t_env_head *env_head)
{
	int		i;
	char	*type;

	i = 1;
	while (cmd[i])
	{
		type = get_type_env(cmd[i]);
		if (!type)
			return (EXIT_FAILURE);
		creation(env_head, cmd[i], type);
		i++;
	}
	g_error_code = 0;
	return (EXIT_SUCCESS);
}
