/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:24:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/22 17:53:07 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_initial_whitespace(char *buffer, t_minish *mini_struct)
{
	while (is_white_space(buffer[mini_struct->i]) == true
		&& buffer[mini_struct->i] != '\0')
	{
		mini_struct->i++;
	}
	if (buffer[mini_struct->i] == '\0')
	{
		free(mini_struct->element);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_words(char *buffer, t_minish *mini_struct)
{
	while (buffer[mini_struct->i])
	{
		if (is_word(buffer, &mini_struct) == -1)
			return (EXIT_FAILURE);
		mini_struct->count_word++;
		while (is_white_space(buffer[mini_struct->i]) == true
			&& buffer[mini_struct->i] != '\0')
			mini_struct->i++;
	}
	return (EXIT_SUCCESS);
}
