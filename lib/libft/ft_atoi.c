/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:02:39 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/27 14:04:58 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	int		sign;
	char	*str;

	str = (char *)nptr;
	result = 0;
	sign = 1;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	if ((*str >= '0') && (*str <= '9'))
	{
		while ((*str >= '0') && (*str <= '9'))
		{
			result = (result * 10) + *str - '0';
			str++;
		}
		return (result * sign);
	}
	return (0);
}
/*
int	main(void)
{
	printf("atoi returns %d\n", atoi("-1    5"));
	printf("ft_atoi returns %d\n", ft_atoi("-1    5"));
}*/
