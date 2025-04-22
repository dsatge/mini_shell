/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:19 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/22 00:59:02 by enschnei         ###   ########.fr       */
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

void	sort_env_array(t_env **arr, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->type, arr[j + 1]->type) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_env_head *env_head)
{
	t_env	**sorted;
	t_env	*tmp;
	int		i;

	sorted = ft_calloc(env_head->size + 1, sizeof(t_env *));
	if (!sorted)
		return (EXIT_FAILURE);
	tmp = env_head->head;
	i = 0;
	while (tmp)
	{
		sorted[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	sort_env_array(sorted, env_head->size);
	i = 0;
	print_declare(sorted);
	free(sorted);
	return (EXIT_SUCCESS);
}

int	ft_export(char **cmd, t_env_head *env_head)
{
	int		i;
	char	*type;

	i = 1;
	if (!cmd[1])
		return (print_sorted_env(env_head));
	while (cmd[i])
	{
		type = get_type_env(cmd[i]);
		if (!type || !is_valid_export_identifier(type))
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", cmd[i]);
			free(type);
			g_error_code = 1;
			i++;
			return(EXIT_FAILURE);
		}
		creation(env_head, cmd[i], type);
		free(type);
		i++;
	}
	g_error_code = 0;
	return (EXIT_SUCCESS);
}
