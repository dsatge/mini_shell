/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:07 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:11:32 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;

	i = atoi(argv[1]);
	(void)argc;
	printf("isprint returns %d\n", isprint(i));
	printf("ft_isprint returns %d\n", ft_isprint(i));
}*/