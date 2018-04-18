/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 23:12:36 by minakim           #+#    #+#             */
/*   Updated: 2018/04/11 23:12:39 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_new_line(int fd, char **data, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (data[fd][i] != '\n' && data[fd][i] != '\0')
		i++;
	if (data[fd][i] == '\n')
	{
		*line = ft_strsub(data[fd], 0, i);
		tmp = ft_strdup(data[fd] + i + 1);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (data[fd][0] == '\0')
			ft_strdel(&data[fd]);
	}
	else if (data[fd][i] == '\0')
	{
		*line = ft_strdup(data[fd]);
		ft_strdel(&data[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			nb_bytes_read_from_buf;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	static char	*data[1024];

	if (fd < 0 || line == NULL)
		return (-1);
	while ((nb_bytes_read_from_buf = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[nb_bytes_read_from_buf] = '\0';
		if (data[fd] == NULL)
			data[fd] = ft_strnew(0);
		tmp = ft_strjoin(data[fd], buf);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (nb_bytes_read_from_buf < 0)
		return (-1);
	else if (nb_bytes_read_from_buf == 0 && data[fd] == NULL)
		return (0);
	return (find_new_line(fd, data, line));
}

/*
** write a function that returns a line read from a file descriptor.
** First, check if the opened fd is available with respective integer value.
** when we open the the file the fd will be set as 3. (b/c 0,1,2 are standards)
** and check to make sure the line is created.
**
** so while the file contains more than 0 byte; we read bytes fromm the buffer.
** set '\0' at the end of buffer.
** I set the if statement saying that if data at fd is NULL then we allocate a memory
** into data at fd. so that the function can manage multiple file descriptors.

** so we first time of reading, the data at fd is equal to NULL and it will allocate
** a memory. I set it as 0 so if you go inside ft_strnew I can see that there is
** a allocated memory with null character.
** tmp will be addressing to the string that we joined data at fd and buf.
** we do ft_strdel to delete the allocated memroy at data[fd].
** then the data[fd] is addressing the string that tmp is also addressing.
** if we find '\n' in the buf we break the while loop.

** if the nbr bytes we read from buf is less than 0 we return -1.

** if nbr bytes is equal to 0 or data[fd] is still NULL then we return 0.

** and we go into find_new_line function to get the '\n' from the data at fd.

** so until the index of data at fd hits '\n', index moves on and when it hits
** '\n', we do ft_strsub to get an allocated memory and return a fresh
** substring from the data[fd] from the beginning(0) until the index(which is '\n')

** and using ft_strdup, we save a copy of string and we are adding index + 1
** so the pointer of data is now at after new line '\n'.
** and delte the allocated memory at data[fd] and the data[fd] will point to
** copy of string we allocated.

** if the data[fd] is a null character then we delete it because there is nothing
*/
