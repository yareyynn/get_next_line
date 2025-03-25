/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakarya <ysakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:53:17 by ysakarya          #+#    #+#             */
/*   Updated: 2025/03/25 05:22:24 by ysakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "fcntl.h"
#include "stdio.h"

char	*trim_store(char *store)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(store[i] != '\n')
		i++;
	i++;
	while (store[i])
		store[j++] = store[i++];
	store[j] = '\0';
	return(store);
}

char	*extract_line(char *store)
{
	int i;
	int j;
	char *line;

	i = 0;
	j = -1;
	while(store[i] != '\n')
		i++;
	line = (char *)malloc(i+2);
	while(++j < i)
		line[j] = store[j];
	line[j] = '\n';
	line[j+1] = '\0';
	return(line);
}


char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	int			bytes_read;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (store == NULL)
	{
		store = (char *)malloc(1);
		*store = '\0';
	}
	while (!ft_strchr(store, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		store = ft_strjoin(store, buffer);
	}
	if (!store || !*store)
	{
		free(buffer);
		return (NULL);
	}
	tmp = extract_line(store);
	store = trim_store(store);
	free(buffer);
	if (*store == '\0')
		free(store);
	return (tmp);
}


int main()
{
	int fd = open("/home/ysakarya/Desktop/get_next_line/yaren", O_RDWR);
	char *line = get_next_line(fd);
	while(line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
	free(line);
}
