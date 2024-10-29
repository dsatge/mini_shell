/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iseven.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:32:41 by dsatge            #+#    #+#             */
/*   Updated: 2024/03/27 15:51:23 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iseven(int c)
{
	int	result;

	result = c / 2;
	result = c % 2;
	if (result == 0)
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_iseven(ft_atoi(argv[1])) == 1)
			write(1, "1", 1);
		if (ft_iseven(ft_atoi(argv[1])) == 0)
			write(1, "0", 1);
	}
	return (0);
}*/
