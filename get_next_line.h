/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:59:37 by penzo             #+#    #+#             */
/*   Updated: 2018/11/26 10:29:55 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h>
# define BUFF_SIZE 16
int     			get_next_line(const int fd, char **line);
//t_dlst				*ft_dlstnew(char const *content, size_t content_size);
typedef struct		s_dlst
{
	char			*content;
	int				fd;
	size_t			content_size;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}					t_dlst;
#endif
