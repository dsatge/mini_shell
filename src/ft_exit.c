/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/16 14:54:42 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_env_head *env_head, char **envp, t_minish *minish)
{
	free_env(env_head);
	ft_freetab(envp);
	free_minish(minish);
	ft_printf(2, "Bisous mon chou <3\n");
	exit(EXIT_SUCCESS);
}
