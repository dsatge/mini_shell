/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:47:49 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:10:24 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;

	i = atoi(argv[1]);
	(void)argc;
	printf("isascii returns %d\n", isascii(i));
	printf("ft_isascii returns %d\n", ft_isascii(i));
}*/
