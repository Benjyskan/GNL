/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:59:37 by penzo             #+#    #+#             */
/*   Updated: 2018/12/02 10:47:50 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# define BUFF_SIZE 100

int					get_next_line(const int fd, char **line);
typedef struct		s_dlst
{
	char			*content;
	int				fd;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}					t_dlst;
#endif
