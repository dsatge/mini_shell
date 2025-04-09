/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:47 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/09 15:28:06 by enschnei         ###   ########.fr       */
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
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void utils_signal_child(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_error_code = 130;
		return ;
	}
	ft_putstr_fd("Quit (core dumped)\n", 2);
	g_error_code = 131;
}

void signal_child(void)
{
	signal(SIGINT, utils_signal_child);
	signal(SIGQUIT, utils_signal_child);
}
