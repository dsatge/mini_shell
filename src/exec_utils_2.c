/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:58 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/09 15:10:21 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**buildtab(t_env_head *env_head)
{
	t_env	*tmp;
	int		i;
	char	**env;
	char	*temp;

	i = 0;
	tmp = env_head->head;
	env = malloc(sizeof(char *) * (env_head->size + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		temp = ft_strjoin(tmp->type, "=");
		if (!temp)
		{
			ft_freetab(env);
			return (NULL);
		}
		env[i] = ft_strjoin(temp, tmp->value);
		free(temp);
		if (!env[i])
		{
			ft_freetab(env);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
