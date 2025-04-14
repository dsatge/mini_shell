/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:04 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/14 16:43:22 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_code(char *res, int *i)
{
	char	*var_value;
	char	*temp;

	var_value = ft_itoa(g_error_code);
	if (!var_value)
		return (NULL);
	temp = ft_strjoin(res, var_value);
	free(var_value);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	free(res);
	*i += 2;
	return (temp);
}

static char	*ft_cheat(char *ptr)
{
	free(ptr);
	return (NULL);
}

static char	*ft_get_env_value(t_env_head *env_head, char *var)
{
	t_env	*tmp;

	tmp = env_head->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*expand_env_variable(char *res, const char *str, int *i,
		t_env_head *env_head)
{
	int		j;
	char	*var_name;
	char	*var_value;
	char	*temp;

	j = *i + 1;
	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - *i - 1);
	if (!var_name)
		return (NULL);
	var_value = ft_get_env_value(env_head, var_name);
	free(var_name);
	if (var_value)
	{
		temp = ft_strjoin(res, var_value);
		if (!temp)
			return (ft_cheat(var_name));
		free(res);
		res = temp;
	}
	*i = j;
	return (res);
}
