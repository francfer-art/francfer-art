/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francfer <francfer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:32:27 by francfer          #+#    #+#             */
/*   Updated: 2023/11/11 11:04:52 by francfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_storage(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
	{
		new_storage = NULL;
		return (ft_free(&storage));
	}
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
		return (ft_free(&storage));
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	ft_free(&storage);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*readbuf(int fd, char *storage)
{
	int		rid;
	char	*buffer;

	rid = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&storage));
	buffer[0] = '\0';
	while (rid > 0 && !ft_strchr(buffer, '\n'))
	{
		rid = read(fd, buffer, BUFFER_SIZE);
		if (rid > 0)
		{
			buffer[rid] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	if (rid == -1)
		return (ft_free(&storage));
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[4096];
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((storage[fd] && !ft_strchr(storage[fd], '\n')) || !storage[fd])
		storage[fd] = readbuf(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = new_line(storage[fd]);
	if (!line)
		return (ft_free(&storage[fd]));
	storage[fd] = clean_storage(storage[fd]);
	return (line);
}

// int main (void)
//{
//	char *linea;
//	int fd,fd2;
//	fd = open("archivo.txt",O_RDONLY);
//	fd2 = open("archivo1.txt",O_RDONLY);
//	linea = get_next_line(fd);
//	printf("%s", linea);
//	linea = get_next_line(fd2);
//	printf("%s", linea);
//	linea = get_next_line(fd);
//	printf("%s", linea);
//	linea = get_next_line(fd2);
//	printf("%s", linea);
//	close(fd);
//	fd = open("archivo.txt",O_RDONLY);
//	linea = get_next_line(fd);
//	printf("%s", linea);
//	linea = get_next_line(fd);
//	printf("%s", linea);
//}