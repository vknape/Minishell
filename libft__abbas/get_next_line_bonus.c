/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 14:32:52 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/14 16:37:29 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_pos(char *temp)
{
	int	pos;

	pos = 0;
	while (temp[pos] != '\n' && temp[pos] != '\0')
		pos++;
	if (temp[pos] == '\n')
		pos++;
	return (pos);
}

static char	*get_remain(char *temp)
{
	char	*remain;
	int		i;
	int		pos;

	i = 0;
	pos = find_pos(temp);
	while (temp[pos + i] != '\0')
		i++;
	remain = malloc((i + 1) * sizeof(char));
	if (!remain)
	{
		free(temp);
		return (NULL);
	}
	i = 0;
	while (temp[pos] != '\0')
	{
		remain[i] = temp[pos];
		i++;
		pos++;
	}
	remain[i] = '\0';
	free(temp);
	return (remain);
}

static char	*get_new_l(char	*temp)
{
	char	*line;
	int		i;
	int		pos;

	i = 0;
	pos = find_pos(temp);
	line = malloc((pos + 1) * sizeof(char));
	if (temp[0] == '\0' || !line)
	{
		free(temp);
		free(line);
		return (NULL);
	}
	while (i < pos)
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*reads_until_newline(int fd, char *temp)
{
	char	*buf;
	int		read_byte;

	buf = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	read_byte = 1;
	while (read_byte > 0)
	{
		if (buf)
			read_byte = read(fd, buf, BUFFER_SIZE);
		if ((read_byte == 0 && temp[0] == '\0') || read_byte < 0 || !buf)
		{
			free(temp);
			free(buf);
			return (NULL);
		}
		buf[read_byte] = '\0';
		temp = ft_strjoin_free(temp, buf);
		if (temp == NULL)
			break ;
		if (ft_strchr(buf, '\n') || read_byte == 0)
			break ;
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!temp[fd])
	{
		temp[fd] = malloc(1 * (sizeof(char)));
		if (!temp[fd])
			return (NULL);
		temp[fd][0] = '\0';
	}
	temp[fd] = reads_until_newline(fd, temp[fd]);
	if (temp[fd] == NULL)
		return (NULL);
	line = get_new_l(temp[fd]);
	if (line != NULL)
		temp[fd] = get_remain(temp[fd]);
	if (line == NULL || temp[fd] == NULL)
	{
		free(line);
		return (ft_free(&temp[fd]));
	}
	return (line);
}
