/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:39:58 by penzo             #+#    #+#             */
/*   Updated: 2018/11/28 12:24:48 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "libft.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define KYEL  "\x1B[33m"
#define KGRN  "\x1B[32m"


//do i need new->length ?

/*	cree new maillon, double chaine
**	et assign une premiere fois content*/
t_dlst	*ft_dlstnew(int fd, t_dlst *prev, t_dlst *next)
{
	t_dlst	*new;
	int		i;
	char	*buff;
	char	*tmp;

	if (!(new = (t_dlst*)malloc(sizeof(t_dlst))))
		return (NULL);
	if (!(buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	new->content = NULL;
	tmp = NULL;
	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		buff[i] = 0;
		if (!(tmp = ft_strjoin(new->content, buff)))
			return (NULL);
		if (new->content)
			free(new->content);
		new->content = tmp;
		ft_bzero(buff, BUFF_SIZE);
		//free(tmp);
	}
	free(buff);
	new->fd = fd;
	new->content_size = ft_strlen(new->content);
	new->prev = prev;
	new->next = next;
	return (new);
}

/*	si fd existe, assign line, free content, assign (content - line)
**	si fd !exist, dlstnew, et le ranger;
**	return: le maillon (existant ou cree)*/
t_dlst	*find_fd(t_dlst *curr, int fd)
{
	if (!curr)//si pas de list
	{
		if (!(curr = ft_dlstnew(fd, NULL, NULL)))
			return (NULL);
		return (curr);
	}
	while (curr->fd < fd && curr->next)
		curr = curr->next;
	while (curr->fd > fd && curr->prev)
		curr = curr->prev;
	//4 cas: 2 extremite, inter, pile dessus
	if (curr->fd == fd)//useless ? vu que je return curr a la fin.
		return (curr);
	//if (!curr->next && curr->fd < fd)//useless
	if (curr->fd < fd)
	{
		curr->next = ft_dlstnew(fd, curr, curr->next);
		curr = curr->next;
	}
	//if (!curr->prev && curr->fd > fd)//usefull
	if (curr->fd > fd)//usefull
	{
		curr->prev = ft_dlstnew(fd, curr->prev, curr);
		curr = curr->prev;
	}
	return (curr);
}

/*set line, reassign content (et content_size ?)*/
char	*get_line(char *content, char **line)
{
	//change line, et return (content - line);
	int		i;
	char	*res;

	i = 0;
	//passer les '\n'
	/*while (content[i] == '\n')
		content++;*/
	//if(content[i] == '\n')//if a la place du while precedent
	//	return (content++);
	while (content[i] && content[i] != '\n')
		i++;
	if (!i)
	{
		//*line = NULL;
		if (!(*line = ft_strnew(0)))
			return (0);
		return (&(content[1]));
		//return (content++);
		//return (NULL);
	}
	if (!(*line = ft_strndup(content, i)))
		return (0);//a voir
	//reassign content
	res = &(content[i + 1]);
	//free(content);
	//free(line);
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static t_dlst	*curr;

	if (read(fd, 0, 0))
		return (-1);
	if (BUFF_SIZE < 1 || fd < 0 || !line)
		return (-1);
	//checker si le fd est deja ouvert
	//si non: create new maillon, le remplir et le ranger
	if (!(curr = find_fd(curr, fd)))
		return (-1);
	//if (!(curr->content))
	if (ft_strcmp(curr->content, "") == 0)
		return (0);
	//assigner line et reassign (content - line)
	//curr->content = get_line(curr->content, line);
	if (!(curr->content = get_line(curr->content, line)))
		return (0);
	//if (curr->content == NULL)
	//	return (0);
	return (1);//meh
}
