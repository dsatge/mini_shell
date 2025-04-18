/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/17 13:36:58 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_env_head *env_head, t_minish *minish)
{
	(void)env_head;
	free_all(minish, 1);
	ft_printf(2, "Bisous mon chou <3\n");
	exit(EXIT_SUCCESS);
}
