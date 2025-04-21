/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:24:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 18:24:39 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_initial_whitespace(char *buffer, int *i, t_minish *mini_struct)
{
	while (is_white_space(buffer[*i]) == true && buffer[*i] != '\0')
		(*i)++;
	if (buffer[*i] == '\0')
	{
		free(mini_struct->element);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_words(char *buffer, int *i, t_minish *mini_struct, int *first_word)
{
	while (buffer[*i])
	{
		if (is_word(buffer, i, &mini_struct, ++(*first_word)) == -1)
			return (EXIT_FAILURE);
		while (is_white_space(buffer[*i]) == true && buffer[*i] != '\0')
			(*i)++;
	}
	return (EXIT_SUCCESS);
}
