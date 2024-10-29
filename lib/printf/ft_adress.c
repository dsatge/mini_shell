/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:25:32 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/28 18:04:36 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(unsigned long ul)
{
	unsigned long	hex;
	int				len;
	char			*base;

	hex = 16;
	len = 0;
	base = "0123456789abcdef";
	if (ul >= hex)
		len += ft_hex(ul / hex);
	len += ft_putchar(base[ul % hex]);
	return (len);
}

int	ft_adress(void *str)
{
	int	len;

	if (!str)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x") + ft_hex((uintptr_t)str);
	return (len);
}
/*
int	main(void)
{
	char	str[12] = "hello world";
	
	ft_adress(str);
}*/
