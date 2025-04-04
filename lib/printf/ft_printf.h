/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:24:04 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 13:28:47 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

unsigned int	ft_putunnbr(unsigned int n, int fd);
int				ft_putstr(char *s, int fd);
int				ft_putnbr(int n, int *len, int fd);
int				ft_hexputnbr(unsigned int n, char c, int fd);
int				ft_adress(void *str, int fd);
int				ft_putchar(char c, int fd);
int				check_type(char c, va_list args, int fd);
int				ft_printf(int fd, const char *c, ...);

#endif