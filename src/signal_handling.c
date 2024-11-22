/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:47 by baiannon          #+#    #+#             */
/*   Updated: 2024/11/15 18:44:43 by baiannon         ###   ########.fr       */
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
	g_error_code = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}