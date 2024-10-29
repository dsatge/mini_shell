/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:19:30 by dsatge            #+#    #+#             */
/*   Updated: 2024/01/12 15:53:00 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (n > 0)
	{
		str[i] = 0;
		i++;
		n--;
	}
}
/*
int	main(void)
{
//	char	s[] = "bonjour";
//	char	s1[] = "bonjour";
	char	*s;
	size_t	n;

	n = 7;
//	bzero(s, n);
	s = ft_calloc(sizeof(char *), n);
	ft_memset(s, '*', 6);
//	ft_memset(s1, '*', 6);
//	printf("bzero came back as %s\n", s);
	printf("ft_calloc came back as %s\n", s);
}*/
