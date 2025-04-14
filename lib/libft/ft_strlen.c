/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:06:45 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/14 14:49:48 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

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
