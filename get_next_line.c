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

int get_next_line(const int fd, char **line)
{
	static t_node *node;
	char s[BUFF_SIZE + 1];
	int id;
	int i;

	i = 0;
	node = (t_node*)malloc(sizeof(t_node));
	while ((id = read(fd, s, BUFF_SIZE)))
	{
		s[id] = '\0';
		ft_putstr(s);
	}
	*line = node->s;
	return (0);
}

int		ft_output(char *str)
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
}

int main(void)
{
	int fd;
	char *line;

	//fd = ft_output("author");
	//if (get_next_line(fd, &line) == 0)
		//ft_putendl(line);
	fd = open("author", O_RDONLY);
	ft_putnbr(get_next_line(fd, &line));
	return (0);
}