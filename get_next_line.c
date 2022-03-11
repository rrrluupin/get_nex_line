/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlupin <rlupin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 04:21:31 by rlupin            #+#    #+#             */
/*   Updated: 2022/01/20 04:21:31 by rlupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_dup(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_next_line(char *progress)
{
	unsigned int		i;
	unsigned int		j;
	char				*str;

	i = 0;
	j = 0;
	while (progress[i] && progress[i] != '\n')
		i++;
	if (!progress[i])
	{
		free(progress);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(progress) - i + 2));
	if (!str)
		return (NULL);
	i++;
	while (progress[i])
		str[j++] = progress[i++];
	free(progress);
	str[j] = '\0';
	return (str);
}

char	*ft_gnl_read(int fd, char *progress)
{
	char	*buf;
	int		res_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	res_read = 1;
	while (!ft_strchr(progress, '\n') && res_read != 0)
	{
		res_read = read(fd, buf, BUFFER_SIZE);
		if (res_read == -1)
		{	
			free(buf);
			return (NULL);
		}
		buf[res_read] = '\0';
		progress = ft_strjoin(progress, buf);
	}
	free(buf);
	return (progress);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*progress;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	progress = ft_gnl_read(fd, progress);
	if (progress == NULL)
		return (NULL);
	line = ft_gnl_dup(progress);
	progress = ft_next_line(progress);
	return (line);
}
