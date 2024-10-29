/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:28:45 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/10 16:18:01 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = (c - 32);
	return (c);
}
/*
int	main(int argc, char **argv)
{
	int	i;

	i = atoi(argv[1]);
	(void)argc;
	printf("toupper returns %d\n", toupper(i));
	printf("ft_toupper returns %d\n", ft_toupper(i));
}*/
