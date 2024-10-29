/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:49:14 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:09:18 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (c);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	
	i = atoi(argv[1]);
	(void)argc;
	printf("isalnum returns %d\n", isalnum(i));
	printf("ft_isalnum %d\n", ft_isalnum(i));
}*/