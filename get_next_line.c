/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:28:52 by ctelma            #+#    #+#             */
/*   Updated: 2019/09/22 21:39:09 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_elements(int fd, t_node **node, char **s)
{
	*s = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!(*node)->fd)
	{
		(*node)->fd = fd;
		(*node)->s = NULL;
		(*node)->next = NULL;
	}
	else if ((*node)->fd != fd)
	{
		while (*node)
		{
			*node = (*node)->next;
			if (!*node)
				*node = (t_node*)malloc(sizeof(t_node));
			if (!(*node)->fd && !(*node)->s)
			{
				(*node)->fd = fd;
				(*node)->s = NULL;
				(*node)->next = NULL;
			}
		}
	}
}

static int	if_end(char *s)
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

static int	push_string(t_node **n, char *s, int flag)
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
		if (if_end(s) == 1 && flag == 1)
			return (1);
	}
	return (0);
}

static char	*check_end(t_node *node)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	while (node->s[i] != '\n')
		i++;
	if (i != 0)
		s = ft_strsub(node->s, 0, i);
	if (node->s[i + 1] == '\0' || !s)
		push_string(&node, NULL, 2);
	else
		push_string(&node, node->s + (i + 1), 2);
	return (s);
}

int			get_next_line(const int fd, char **line)
{
	static t_node	*node;
	t_node			*n;
	char			*s;
	int				id;
	int 			ch;

	if (fd == -1)
		return (-1);
	if (!node)
		node = (t_node*)malloc(sizeof(t_node));
	n = node;
	create_elements(fd, &n, &s);
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
	else if (!n->s && id - 1 < BUFF_SIZE)
		ch = 0;
	free(s);
	return (ch);
}

int main(void) {
	int fd;
	int fd1;
	char *line;
	char *line1;

	fd = open("test", O_RDONLY);
	if (get_next_line(fd, &line) < 2)
	 	ft_putstr(line);
	ft_putchar('\n');
	if (get_next_line(fd, &line) < 2)
		ft_putstr(line);
	ft_putchar('\n');
	if (get_next_line(fd, &line) < 2)
		ft_putstr(line);
	/*fd1 = open("author", O_RDONLY);
	if (get_next_line(fd1, &line1) == 1)
		ft_putstr(line1);
	ft_putchar('\n');
	if (get_next_line(fd1, &line1) == 1)
		ft_putstr(line1);
	ft_putchar('\n');*/
	return (0);
}