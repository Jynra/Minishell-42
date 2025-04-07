/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:39:00 by ellucas           #+#    #+#             */
/*   Updated: 2024/12/06 15:00:31 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*extract_line(char **storage)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
		line = ft_substr(*storage, 0, i + 1);
	else
		line = ft_substr(*storage, 0, i);
	temp = ft_strdup(&((*storage)[i + ((*storage)[i] == '\n')]));
	free(*storage);
	*storage = temp;
	return (line);
}

static int	read_and_store(int fd, char **storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = temp;
		if (ft_strchr(*storage, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	int			result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	result = read_and_store(fd, &storage);
	if (result < 0 || (result == 0 && !*storage))
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	return (extract_line(&storage));
}
