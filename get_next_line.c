/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blidriss <blidriss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:33:39 by blidriss          #+#    #+#             */
/*   Updated: 2025/11/22 13:56:46 by blidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		if (count == 0)
			break ;
		buff[count] = '\0';
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
	size_t	x;
	size_t	i;

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
	static char	*leftover;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!leftover)
		leftover = ft_calloc(1, 1);
	if (!leftover)
		return (NULL);
	leftover = get_read_file(fd, leftover);
	if (!leftover)
		return (NULL);
	line = get_fist_line(leftover);
	if (!line || !line[0])
	{
		free(leftover);
		leftover = NULL;
		free(line);
		return (NULL);
	}
	leftover = get_after_line(leftover);
	if (!leftover)
		return (free(line), NULL);
	return (line);
}
