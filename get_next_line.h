/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctelma <ctelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:29:35 by ctelma            #+#    #+#             */
/*   Updated: 2019/09/19 14:48:56 by ctelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"

# include <fcntl.h>

# define BUFF_SIZE 32

typedef struct	s_node t_node;

struct	s_node
{
	char	*s;
	int 	fd;
	t_node	*next;
};

int		get_next_line(const int fd, char **line);

#endif
