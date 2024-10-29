/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:19:30 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/08 15:20:04 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	int				i;

	str = (unsigned char *)s;
	i = 0;
	while (n > '0' - 48)
	{
		if (str[i] == (unsigned char)c)
		{
			return (&str[i]);
		}
		i++;
		n--;
	}
	return (NULL);
}
/*
int	main(void)
{
//	char	*s = "";
	char	*sf = "";
	int	c;
	size_t	n;
	
	c = atoi("5");
	n = 14;
//	s = memchr(s, c, n);
	sf = ft_memchr(sf, c, n);
	printf("c is %i", c);
//	printf("memchr returns %c %p\n", *s, s);
	printf("ft_memchr returns %c %p\n", *sf, sf);
}*/
