/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:23:37 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 15:17:34 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env *target)
{
	free(target->type);
	free(target->value);
	target->type = NULL;
	target->value = NULL;
	free(target);
}

static void	delete_node(t_env_head *env_head, t_env *target)
{
	t_env	*current;
	t_env	*prev;

	if (!env_head || !env_head->head || !target)
		return ;

	current = env_head->head;
	prev = NULL;

	if (current == target)
	{
		env_head->head = current->next;
		free_node(target);
		env_head->size--;
		return ;
	}

	while (current && current != target)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_node(current);
		env_head->size--;
	}
}

static t_env *find_env_node(t_env *env, char *thing)
{
	while (env)
	{
		if (ft_strcmp(env->type, thing) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}

void	ft_unset(char **cmds, t_env_head *env_head)
{
	int		i;
	t_env	*target;

	if (!cmds || !env_head || !env_head->head)
		return ;
	i = 1;
	while (cmds[i])
	{
		target = find_env_node(env_head->head, cmds[i]);
		if (target)
			delete_node(env_head, target);
		i++;
	}
	g_error_code = 0;
}
