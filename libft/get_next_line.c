/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 15:24:12 by adakheel      #+#    #+#                 */
/*   Updated: 2024/03/21 10:40:56 by adakheel      ########   odam.nl         */
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
		remain[i++] = temp[pos++];
	remain[i] = '\0';
	free(temp);
	if (remain[0] == '\0')
	{
		free(remain);
		return (NULL);
	}
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
	static char	*temp = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!temp)
	{
		temp = malloc(1 * (sizeof(char)));
		if (!temp)
			return (NULL);
		temp[0] = '\0';
	}
	temp = reads_until_newline(fd, temp);
	if (temp == NULL)
		return (NULL);
	line = get_new_l(temp);
	if (line != NULL)
		temp = get_remain(temp);
	if (line == NULL)
	{
		free(line);
		return (ft_free(&temp));
	}
	return (line);
}
