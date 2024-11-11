/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:40:34 by baiannon          #+#    #+#             */
/*   Updated: 2024/11/11 04:27:38 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    free_tokenList(t_token *list)
{
    t_token *temp;

    while (list)
    {
        temp = list->next;
        free(list->str);
        free(list);
        list = temp;
    }
}

static void    free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return;
    while(tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    free_all(t_token *list, char **tab)
{
    free_tab(tab);
    free_tokenList(list);
}