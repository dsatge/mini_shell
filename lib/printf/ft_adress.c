/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:25:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 13:26:10 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(unsigned long ul, int fd)
{
	unsigned long	hex;
	int				len;
	char			*base;

	hex = 16;
	len = 0;
	base = "0123456789abcdef";
	if (ul >= hex)
		len += ft_hex(ul / hex, fd);
	len += ft_putchar(base[ul % hex], fd);
	return (len);
}

int	ft_adress(void *str, int fd)
{
	int	len;

	if (!str)
		return (ft_putstr("(nil)", fd));
	len = ft_putstr("0x", fd) + ft_hex((uintptr_t)str, fd);
	return (len);
}
/*
int	main(void)
{
	char	str[12] = "hello world";
	
	ft_adress(str);
}*/
