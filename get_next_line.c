/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:12:00 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/21 16:10:15 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	clean_list(t_list **list)
{
	t_list	*tmp;
	if (*list == NULL)
		return ;
	tmp = *list;
	while (tmp -> next != NULL)
	{
		tmp = (*list) -> next;
		free((*list) -> str);
		free(*list);
		*list = tmp;
	}
}

void	charsleft(t_list *list)
{
	char		*cleft;
	t_list		*lastnode;
	t_list		*remaindernode;
	int			i;
	int			k;

	i = 0;
	k = 0;
	remaindernode = malloc(sizeof (t_list));
	if (!remaindernode)
		return ;
	cleft = malloc(BUFFER_SIZE + 1);
	if (!cleft)
		return ;
	while (list -> str[i] && list -> str[i] != '\n')
		i++;
	while (list -> str[i] && list -> str[++i])
		cleft[k++] = list -> str[i];
	cleft[k] = '\0';
	remaindernode -> str = cleft;
	remaindernode -> next = NULL;
	free(cleft);
	clean_list(&list);
}

int	lenofstring(t_list *list)
{
	int	len;

	while (list)
	{
		len = 0;
		while (list -> str[len] && list -> str[len] != '\n')
		{
			len++;
		}
		list = list -> next;
	}
	return (len);
}

char	*copystr(t_list *list)
{
	char	*full_line;
	int		strlen;
	int		i;
	int		k;

	k = 0;
	strlen = (lenofstring(list));
	full_line = malloc(strlen +1);
	if (!full_line)
		return (NULL);
	while (list)
	{
		i = 0;
		while (list -> str[i])
		{
			if (list -> str[i] == '\n')
			{
				i++;
				full_line[k] = '\0';
			}
			full_line[k++] = list -> str[i++];
		}
		list = list -> next;
	}
	return (full_line);
}

void	addnode(t_list **list, char *buf)
{
	t_list	*newnode;
	t_list	*last;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return ;
	last = lastnode(*list);
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
	nextline = copystr(list);
	charsleft(list);
	return (nextline);
}