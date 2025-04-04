/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:23:50 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 13:17:44 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)", fd));
	while (s[i])
	{
		ft_putchar(s[i], fd);
		i++;
	}
	return (i);
}
