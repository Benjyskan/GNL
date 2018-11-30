/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:38:54 by penzo             #+#    #+#             */
/*   Updated: 2018/11/30 18:47:16 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	init curr->content
*/

char	*init_content(const int fd)
{
	int		i;
	char	*buff;
	char	*tmp;
	char	*content;

	if (!(buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	//ft_bzero(buff, BUFF_SIZE);//aucun effet :/
	content = NULL;
	i = 0;//useless
	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		buff[i] = 0;
		tmp = ft_strjoin(content, buff);
		if (content)
			free(content);
		content = tmp;
		ft_bzero(buff, BUFF_SIZE);
	}
	ft_putstr("content: ");
	ft_putchar(content[0]);
	ft_putchar(content[1]);
	ft_putchar(content[2]);
	ft_putchar('\n');
	free(buff);
	return (content);
}

/*
**	create a new element:
**	malloc an elem
**	init_content new->content
*/

t_dlst	*ft_dlstnew(int fd, t_dlst *prev, t_dlst *next)
{
	t_dlst	*new;

	if (!(new = (t_dlst*)malloc(sizeof(t_dlst))))
		return (NULL);
	new->content = init_content(fd);
	new->fd = fd;
	new->prev = prev;
	new->next = next;
	return (new);
}

/*
**	set line
**	return (content - line)
*/

char	*get_line(char *content, char **line)
{
	int		i;

	i = 0;
	while (content && content[i] && content[i] != '\n')
		i++;
	*line = ft_strndup(content, i);
	return (&(content[i + 1]));
}

/*
**	find fd, if can't:
**	-->create it
*/

t_dlst	*find_fd(t_dlst *curr, const int fd)
{
	if (!curr)
	{
		if (!(curr = ft_dlstnew(fd, NULL, NULL)))
			return (NULL);
		return (curr);
	}
	while (curr->fd < fd && curr->next)
		curr = curr->next;
	while (curr->fd > fd && curr->prev)
		curr = curr->prev;
	if (curr->fd < fd)
	{
		curr->next = ft_dlstnew(fd, curr, curr->next);
		curr = curr->next;
	}
	if (curr->fd > fd)
	{
		curr->prev = ft_dlstnew(fd, curr->prev, curr);
		curr = curr->prev;
	}
	return (curr);
}

/*
**	1. basic check
**	2. find the chain elem
**	3. check if fd->content change
**	4. get_line
*/

int		get_next_line(const int fd, char **line)
{
	ft_putendl("GNL Begining");
	static t_dlst	*curr = NULL;
	char			*tejme;
	tejme = (char*)malloc(sizeof(char));

	if (read(fd, 0, 0) || BUFF_SIZE < 1 || fd < 0 || !line)
		return (-1);
	curr = find_fd(curr, fd);
	//check curr->content
	//if the fd files change, and I finished read the previous one
	//if ((read(curr->fd, tejme, 1) > 0) && (curr->content[0] == 0))//working
	if ((read(curr->fd, tejme, 1) > 0) && (curr->content[0] == 0))
	{
		ft_putendl("YOYOYOYOYOYOYOYOYOYOYOYOYO");
		printf("tejme: %s\n", tejme);
		//curr->content[0] = tejme[0];
		//curr->content = init_content(curr->fd);//reassign content
		curr->content = init_content(fd);//reassign content
		curr->content = ft_strjoin(tejme, curr->content);
	}
	//if all lines were read
	if (curr->content[0] == 0)
	{
		ft_putendl("I'm in !, content is empty");
		system("cat ~/42FileChecker/moulitest_42projects/get_next_line_tests/sandbox/one_big_fat_line.txt | cut -c 1-5; cat ~/42FileChecker/moulitest_42projects/get_next_line_tests/sandbox/one_big_fat_line.txt.mine | cut -c 1-5");
		return (0);
	}
	//set line and content to (content - line)
	curr->content = get_line(curr->content, line);
	return (1);
}
