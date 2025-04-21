/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:18:35 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/22 00:59:22 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_declare(t_env **sorted)
{
	int	i;

	i = 0;
	while (sorted[i])
	{
		if (sorted[i]->type)
		{
			if (sorted[i]->value)
				ft_printf(1, "declare -x %s=\"%s\"\n", sorted[i]->type,
					sorted[i]->value);
			else
				ft_printf(1, "declare -x %s\n", sorted[i]->type);
		}
		i++;
	}
	return ;
}

int	is_valid_export_identifier(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
