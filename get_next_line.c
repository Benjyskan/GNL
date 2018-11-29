/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:39:58 by penzo             #+#    #+#             */
/*   Updated: 2018/11/29 18:31:17 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "libft.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define KYEL  "\x1B[33m"
#define KGRN  "\x1B[32m"



char    *ft_strjoinfree(char const *s1, char const *s2)//nothing changed yet
{
	char    *res;
	int     len;
	int     i;
	int     j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = ft_strnew(len)))//
		return (NULL);
	ft_strcpy(res, s1);//
	/*i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}*/
	//res[i] = 0;
	//-------
	i = ft_strlen(s1);
	j = 0;
	while (i < len)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	//ft_putstr("len: ");
	//ft_putnbr(len);
	//ft_putendl("");
	return (res);
}

//do i need new->length ?

/*	cree new maillon, double chaine
**	et assign une premiere fois content*/
t_dlst	*ft_dlstnew(int fd, t_dlst *prev, t_dlst *next)
{
	t_dlst	*new;
	int		i;
	char	*buff;
	char	*tmp;

	ft_putendl("Begin lstnew");
	if (!(new = (t_dlst*)malloc(sizeof(t_dlst))))
		return (NULL);
	if (!(buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	new->content = NULL;
	tmp = NULL;
	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		buff[i] = 0;
		if (!(tmp = ft_strjoinfree(new->content, buff)))
			return (NULL);
		if (new->content)
			free(new->content);
		new->content = tmp;
		ft_bzero(buff, BUFF_SIZE);
		//free(tmp);
	}
	free(buff);
	new->fd = fd;
	//ft_putstr("len: ");
	//ft_putnbr(ft_strlen(new->content));
	//ft_putendl("");

	new->content_size = ft_strlen(new->content);
	//ft_putstr("cont_size: ");
	//ft_putnbr(new->content_size);
	//ft_putendl("");
	new->prev = prev;
	new->next = next;
	return (new);
}

/*	si fd existe, assign line, free content, assign (content - line)
 **	si fd !exist, dlstnew, et le ranger;
 **	return: le maillon (existant ou cree)*/
t_dlst	*find_fd(t_dlst *curr, int fd)
{
	/*ft_putendl("entering find-fd");
	ft_putendl(curr->content);
	ft_putnbr(curr->fd);*/
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
//	//if (curr->fd == fd)//useless ? vu que je return curr a la fin.
//	//	return (curr);
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
	ft_putendl("enter get_line");
	int		i;
	char	*res;

	i = 0;
	//if(content[i] == '\n')
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
	static t_dlst	*curr = NULL;

	if (read(fd, 0, 0))
		return (-1);
	if (BUFF_SIZE < 1 || fd < 0 || !line)
		return (-1);
	//checker si le fd est deja ouvert
	//si non: create new maillon, le remplir et le ranger
	
	if (!(curr = find_fd(curr, fd)))
	{
		return (-1);
	}
	//if (!(curr->content))
	//Au choix.
	//if (ft_strcmp(curr->content, "") == 0)
	//	return (0);
	
	ft_putendl("prout");
	ft_putnbr(curr->fd);
	if (curr->content[0] == 0)
	{
		ft_putendl("HEY");
		//printf("curr->content: %s\n", curr->content);
		if(!(*line = ft_strnew(0)))//ajoute pour pouvoir free
			return (-1);
		//ft_putendl("Content[0] == 0 !");
		//free(curr->content);//last change/////////
		return (0);
	}

	//assigner line et reassign (content - line)
	//curr->content = get_line(curr->content, line);
	if (!(curr->content = get_line(curr->content, line)))
	{
		return (0);
	}
	ft_putendl("Bonsoir");
	//if (curr->content == NULL)
	//	return (0);
	return (1);//meh
}
