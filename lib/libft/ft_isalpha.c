/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:14:39 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:19:27 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	i = atoi(argv[1]);
	printf("ft_isalpha returns %d\n", ft_isalpha(i));
	printf("isalpha returns %d\n", isalpha(i));
	return (argc);
}*/
