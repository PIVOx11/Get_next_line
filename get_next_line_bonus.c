/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blidriss <blidriss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:30:08 by blidriss          #+#    #+#             */
/*   Updated: 2025/11/23 05:20:04 by blidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_read_file(int fd, char *leftover)
{
	char	*buff;
	char	*tmp;
	ssize_t	count;

	count = 1;
	buff = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buff)
		return (free(leftover), NULL);
	while (!ft_strchr(leftover, '\n') && count > 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
			return (free(leftover), free(buff), NULL);
		buff[count] = '\0';
		if (count == 0)
			break ;
		tmp = ft_strjoin(leftover, buff);
		if (!tmp)
			return (free(leftover), free(buff), NULL);
		free(leftover);
		leftover = tmp;
	}
	free(buff);
	return (leftover);
}

char	*get_fist_line(char *leftover)
{
	char	*line;
	size_t	i;
	size_t	x;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	x = 0;
	while (x < i)
	{
		line[x] = leftover[x];
		x++;
	}
	if (leftover[x] == '\n')
		line[x++] = '\n';
	return (line);
}

char	*get_after_line(char *leftover)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	len = ft_strlen(leftover + i);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
	{
		free(tmp);
		free(leftover);
		return (NULL);
	}
	if (leftover[i] == '\n')
		i++;
	len = 0;
	while (leftover[i])
		tmp[len++] = leftover[i++];
	free(leftover);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*leftover[MAX_OPEN];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd > MAX_OPEN || fd < 0)
		return (NULL);
	if (!leftover[fd])
		leftover[fd] = ft_calloc(1, 1);
	if (!leftover[fd])
		return (NULL);
	leftover[fd] = get_read_file(fd, leftover[fd]);
	if (!leftover[fd])
		return (NULL);
	line = get_fist_line(leftover[fd]);
	if (!line || !line[0])
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
		free(line);
		return (NULL);
	}
	leftover[fd] = get_after_line(leftover[fd]);
	if (!leftover[fd])
		return (free(line), NULL);
	return (line);
}
