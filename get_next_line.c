/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:47:54 by ctelma            #+#    #+#             */
/*   Updated: 2019/09/23 19:07:49 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_node	*find_elem(int fd, t_node **node)
{
	t_node *cur;
	t_node *new;

	cur = *node;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	if (!(new = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	new->fd = fd;
	new->s = NULL;
	new->next = *node;
	*node = new;
	return (new);
}

static int		push_string(t_node **n, char *s, int flag)
{
	char *str;

	if (flag == 1)
	{
		if (!(*n)->s)
			str = ft_strdup(s);
		else
			str = ft_strjoin((*n)->s, s);
	}
	else if (s != NULL)
		str = ft_strdup(s);
	if (s == NULL)
	{
		free((*n)->s);
		(*n)->s = NULL;
	}
	else
	{
		free((*n)->s);
		(*n)->s = str;
		if (ft_strchr(s, '\n') != 0)
			return (1);
	}
	return (0);
}

static char		*check_end(t_node *node)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	while (node->s[i] != '\n' && node->s[i] != '\0')
		i++;
	if (i != 0)
		s = ft_strsub(node->s, 0, i);
	if (node->s[i + 1] == '\0' || !s || node->s[i] == '\0')
		push_string(&node, NULL, 2);
	else
		push_string(&node, node->s + (i + 1), 2);
	return (s);
}

int				get_next_line(const int fd, char **line)
{
	static t_node	*node;
	t_node			*n;
	char			s[BUFF_SIZE + 1];
	int				id;
	int				ch;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	n = find_elem(fd, &node);
	while ((id = read(fd, s, BUFF_SIZE)))
	{
		s[id] = '\0';
		if (push_string(&n, s, 1) == 1)
			break ;
	}
	if (n->s)
	{
		*line = check_end(n);
		ch = 1;
	}
	if (!*line && !(n->s) && id == 0 && ch != 1)
		ch = 0;
	return (ch);
}


int		main(void)
{
	int fd;
	int fd1;
	char *s;
	int id;

	fd = open("test", O_WRONLY);
	fd1 = open("test", O_RDONLY);
	write(fd, "abc\n\n", 5);
	id = get_next_line(fd1, &s);
	ft_putendl(s);
	ft_putnbr(id);
	ft_putchar('\n');
	id = get_next_line(fd1, &s);
	ft_putendl(s);
	ft_putnbr(id);
	ft_putchar('\n');
	id = get_next_line(fd1, &s);
	ft_putendl(s);
	ft_putnbr(id);
	id = get_next_line(fd1, &s);
	ft_putendl(s);
	ft_putnbr(id);
	ft_putchar('\n');

}