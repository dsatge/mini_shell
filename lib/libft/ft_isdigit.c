/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:20:36 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:20:28 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	
	(void)argc;
	i = atoi(argv[1]);
	printf("isdigit returns %d\n", isdigit(i));
	printf("ft_isdigit returns %d\n", ft_isdigit(i)); 
}*/
