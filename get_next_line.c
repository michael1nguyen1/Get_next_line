/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:12:00 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/18 14:20:33 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


t_list *lastnode(t_list *list)
{
	while (list != NULL)
	{
		if (list -> next == NULL)
			return (list);
		list = list -> next;
	}
	return (list);
}

void	addnode(t_list **list, char *buf)
{
t_list *newnode;
t_list *last;

newnode = malloc(sizeof(t_list));
if (!newnode)
	return ;
last = lastnode(list);
newnode -> str = buf;
if (last != NULL)
	last -> next = newnode;
else
	*list = newnode;
newnode -> next = NULL;
}

int	find_line(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str[i] && i < BUFFER_SIZE)
		{
			if (list->str[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	make_list(t_list **list, int fd)
{
	int		buff_read;
	char	*buf;

	while (!find_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		buff_read = read(fd, buf, BUFFER_SIZE);
		if (!buff_read)
			return ;
		buf[buff_read] = '\0';
		addnode(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, &nextline, 0) < 0)
		return (NULL);
	make_list(&list, fd);
	if (list == NULL)
		return (NULL);
	nextline = get_next(list);
	clean_list_(&list);
	return (nextline);
}
