/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:06:45 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/11 03:11:22 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;

	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;
	printf("strlen returns %ld\n", strlen(argv[1]));
	printf("ft_strlen returns %ld\n", ft_strlen(argv[1]));
}*/
