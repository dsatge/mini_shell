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

int ft_pwd(char **cmd)
{
    (void)cmd;
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("PWD Error");
        return (1);
    }
    ft_printf("%s\n", cwd);
    free(cwd);
    return (0);
}