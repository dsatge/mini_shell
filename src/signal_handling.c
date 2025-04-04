/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:47 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 13:36:39 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(void)
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handle(int signal)
{
	g_error_code = signal + 128;
	ft_printf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}