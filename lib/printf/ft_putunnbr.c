/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:33:04 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/13 16:44:50 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putunnbr(unsigned int un)
{
	int	len;

	len = 0;
	if (un > 9)
		len += ft_putunnbr(un / 10);
	len += ft_putchar(un % 10 + '0');
	return (len);
}
/*
int	main(void)
{
	int	n;

	n = -2148;
	ft_putunnbr(n);
}*/
