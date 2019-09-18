/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:28:52 by ctelma            #+#    #+#             */
/*   Updated: 2019/09/15 20:08:45 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char     *check_end(t_node *node)
{
	size_t i;
	char *s;

	i =0;
	while (node->s[i] != '\n')
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s = ft_strsub(node->s, 0, i);
	return (s);
}

int get_next_line(const int fd, char **line)
{
	static t_node *node;
	char *s;
	int id;

	s = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	node = (t_node*)malloc(sizeof(t_node));
	node->fd = fd;
	node->s = NULL;
	while ((id = read(fd, s, BUFF_SIZE)))
	{
        s[id] = '\0';
	    if (!node->s)
	        node->s = ft_strdup(s);
	    else
	    	node->s = ft_strjoin(node->s, s);
	}
	*line = check_end(node);
	return (0);
}

/*int		ft_output(char *str)
{
	int		fd;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("open() error\n");
		return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ft_putstr(buf);
	}
	if (close(fd) == -1)
	{
		ft_putstr("close() error\n");
		return (1);
	}
	return (fd);
}*/

int main(void)
{
	int fd;
	char *line;

	fd = open("author", O_RDONLY);
	if (get_next_line(fd, &line) == 0)
	    ft_putstr(line);
	return (0);
}