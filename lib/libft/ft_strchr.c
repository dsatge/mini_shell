/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:25:06 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/27 18:00:06 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	else
		return (0);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	char	*str;
	char	*ftstr;

	i = atoi(argv[2]);
	str = strchr(argv[1], i);
	ftstr = ft_strchr(argv[1], i);
	if (str == ftstr)
		printf("returns same thing");
	else
		printf("different, mistake here");
}*/
