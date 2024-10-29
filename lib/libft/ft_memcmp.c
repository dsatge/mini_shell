/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:23:09 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/27 17:37:10 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	s1[] = "";
	char	s2[] = "Hello Aolly";
	int	n;
	int	i;
	int	j;

	n = 0;
	i = memcmp(s1, s2, n);
	printf("memcmp returns %i\n", i);
	j = ft_memcmp(s1, s2, n);
	printf("ft_memcmp returns %i\n", j);
}
*/
