/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:28:52 by ctelma            #+#    #+#             */
/*   Updated: 2019/09/19 19:29:56 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		create_elements(int fd, t_node **node, char **s)
{
	*s = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	*node = (t_node*)malloc(sizeof(t_node));
	if (!(*node)->fd)
	{
		(*node)->fd = fd;
		(*node)->s = NULL;
	}
	else if ((*node)->fd != fd)
	{
		while ((*node)->next)
		{
			*node = (*node)->next;
			if ((*node)->fd == fd)
				break;
		}
		*node = (*node)->next;
		(*node)->fd = fd;
		(*node)->s = NULL;
	}
}

static int 		if_end(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void		push_string(t_node **n, char *s, int flag)
{
	char *str;

	if (flag == 1)
	{
		if (!(*n)->s)
			str = ft_strdup(s);
		else
			str = ft_strjoin((*n)->s, s);
	}
	else if (flag == 2)
		str = ft_strdup(s);
	free((*n)->s);
	(*n)->s = str;
}

static char     *check_end(t_node *node)
{
	size_t	i;
	char 	*s;

	i =0;
	while (node->s[i] != '\n')
		i++;
	s = ft_strsub(node->s, 0, i);
	push_string(&node, node->s + (i + 1), 2);
	return (s);
}

int				get_next_line(const int fd, char **line)
{
	static t_node	*node;
	t_node			*n;
	char			*s;
	int				id;

	n = node;
	create_elements(fd, &n, &s);
	while ((id = read(fd, s, BUFF_SIZE)))
	{
        s[id] = '\0';
		if (if_end(s) == 1)
		{
			push_string(&n, s, 1);
			break;
		}
		else
	    	push_string(&n, s, 1);
	}
	*line = check_end(n);
	free(s);
	return (1);
}

int main(void)
{
	int fd;
	char *line;
	char *line1;

	/*fd = open("author", O_RDONLY);
	if (get_next_line(fd, &line) == 1)
	    ft_putstr(line);
	ft_putchar('\n');
	if (get_next_line(fd, &line) == 1)
		ft_putstr(line);
	ft_putchar('\n');*/
	fd = open("test", O_RDONLY);
	if (get_next_line(fd, &line1) == 1)
		ft_putstr(line1);
	ft_putchar('\n');
	//fd = open("test", O_RDONLY);
	if (get_next_line(fd, &line1) == 1)
		ft_putstr(line1);
	return (0);
}