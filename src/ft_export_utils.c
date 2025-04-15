/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:18:35 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/15 19:22:18 by dsatge           ###   ########.fr       */
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
