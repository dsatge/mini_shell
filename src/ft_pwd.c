/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:13:48 by baiannon          #+#    #+#             */
/*   Updated: 2024/12/04 17:17:10 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_token *cmd)
{
    cmd->str = getcwd(NULL, 0);
    if (!cmd->str) 
    {
        perror("PWD Error");
        return (1);
    }
    ft_printf("%s\n", cmd->str);
    return (0);
}