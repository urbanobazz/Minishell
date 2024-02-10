/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:14:57 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/25 14:40:06 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_block(int fd, char **line, char *buffer);
static void	extract_output_line(char **output, char **line);
static void	reset_line_buffer(char	**line_buffer);

char	*get_next_line(int fd)
{
	static char	*line_buffer; //contains remainder
	char		*temp_buffer; //temporary storage space
	char		*output;
	int			read_bytes; //used to identify end of the line.

	if (fd < 0 || BUFFER_SIZE <= 0) //Check if temp_buffer and fd are valid.
		return (NULL);
	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	read_bytes = 1;
	while ((!ft_strchr(line_buffer, '\n')) && read_bytes > 0)
		read_bytes = read_block(fd, &line_buffer, temp_buffer);
	free(temp_buffer);
	if (read_bytes == -1)
		return (NULL);
	if (ft_strlen(line_buffer) == 0)
		return (NULL);
	extract_output_line(&output, &line_buffer);
	reset_line_buffer(&line_buffer);
	return (output);
}

/* This function reads the file/line into the temporary temp_buffer, checking for the end of the file in every iteration.
 if it could read, it will update the line to hold it's previous content plus what was read last.
 if nothing can be read(end of file found), it sets line to NULL and returns an error to outer function.*/

static int	read_block(int fd, char **line, char *buffer)
{
	char	*temp;
	int		bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes == 0)
		return (bytes);
	if (bytes == -1 || buffer == NULL) // checks/handles end of the file
		return (free(*line), *line = NULL, -1);
	temp = ft_strjoin(*line, buffer);
	free(*line);
	*line = temp;
	return (bytes);
}

/* This function takes the temp_buffer and extracts the line to be output (everything until the '/n').
It then stores it in the output variable, to be later returned by the main function */

static void	extract_output_line(char **output, char **line)
{
	char	*remainder;
	int		len;

	remainder = ft_strchr(*line, '\n');
	len = ft_strlen(*line) - ft_strlen(remainder) + 2; //gets the length of output, till new line (+2 because strlen doesn't count it).
	*output = (char *)malloc(len * sizeof(char));
	if (!output)
		return ;
	ft_strlcpy(*output, *line, len);
}

/* This function resets the line_buffer to hold only the remainder after the output string, if there is any. */
static void	reset_line_buffer(char	**line_buffer)
{
	char	*remainder;
	char	*temp;

	remainder = ft_strchr(*line_buffer, '\n');
	if (!remainder)
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return ;
	}
	temp = malloc((ft_strlen(remainder)) * sizeof(char));
	if (!temp)
		return ;
	ft_strlcpy(temp, remainder + 1, ft_strlen(remainder));
	free(*line_buffer);
	*line_buffer = temp;
	if (**line_buffer == 0)
	{
		free(*line_buffer);
		*line_buffer = NULL;
	}
}

