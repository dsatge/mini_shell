/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:14:04 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/08 10:23:46 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
int	main(int argc, char **argv)
ize_t  ft_strlen(const char *s)

	int	i;

	i = atoi(argv[1]);
	(void)argc;
	printf("tolower returns %d\n", tolower(i));
	printf("ft_tolower returns %d\n", ft_tolower(i));
}*/
