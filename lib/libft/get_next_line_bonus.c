/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:46:25 by dsatge            #+#    #+#             */
/*   Updated: 2024/09/03 14:35:01 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

static char	*read_line(int fd, char *saved)
{
	char	*buff;
	char	*temp;
	int		i;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (!saved)
		saved = ft_strdup("\0");
	i = 1;
	while (!ft_strchr(saved, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			free(saved);
			return (NULL);
		}
		buff[i] = '\0';
		temp = saved;
		saved = ft_strjoin(saved, buff);
		free (temp);
	}
	return (free(buff), saved);
}

static char	*get_line(char *saved)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		new_str[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		new_str[i] = saved[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	*new_saved(char *saved)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (free (saved), NULL);
	str = malloc(sizeof(char) * ((ft_strlen(saved) - i + 1)));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		str[j++] = saved[i++];
	str[j] = '\0';
	free (saved);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved[fd] = read_line(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = get_line(saved[fd]);
	saved[fd] = new_saved(saved[fd]);
	if (!line && saved[fd])
		free(saved[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*gnl;

	fd = open("longfile.txt", O_RDONLY);
	while ((gnl = get_next_line(fd)) != NULL )
	{
		printf("GNL = %s\n", gnl);
		free(gnl);
	}
	free(gnl);
	return (0);
}*/
