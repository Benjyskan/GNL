/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:59:37 by penzo             #+#    #+#             */
/*   Updated: 2018/11/24 14:46:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# define BUFF_SIZE 2
int     			get_next_line(const int fd, char **line);
t_dlist				*ft_dlstnew(char const *content, size_t content_size);
typedef struct		s_dlist
{
	char			*content;
	int				fd;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;
#endif
