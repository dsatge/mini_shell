/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:48:44 by dsatge            #+#    #+#             */
/*   Updated: 2024/03/07 15:16:39 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (-1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("= %i\n", ft_strcmp(argv[1], argv[2]));
	}
	return (0);
}*/
