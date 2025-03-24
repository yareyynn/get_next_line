#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (dstsize-- > 1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

static char	*get_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		len;

	len = 0;
	while ((*buffer)[len] && (*buffer)[len] != '\n')
		len++;
	if ((*buffer)[len] == '\n')
		len++;
	line = ft_substr(*buffer, 0, len);
	temp = ft_strdup(*buffer + len);
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		temp = ft_strjoin(buffer, buf);
		free(buffer);
		buffer = temp;
	}
	if (!buffer || !*buffer)
		return (NULL);
	return (get_line(&buffer));
}
