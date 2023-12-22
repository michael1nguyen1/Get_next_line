/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:12:00 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/22 22:19:44 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	copy_str(t_list *list, char *full_line)
{
	int	i;
	int	k;

	k = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				full_line[k++] = '\n';
				full_line[k] = '\0';
				return;
			}
			full_line[k++] = list->str[i++];
		}
		list = list->next;
	}
	full_line[k] = '\0';
}

static char	*makestr(t_list *list)
{
	char	*full_line;
	int		strlen;

	strlen = (lenofstring(list));
	full_line = malloc(strlen +1);
	if (!full_line)
		return (NULL);
		copy_str(list, full_line);
	return (full_line);
}

static void	charsleft(t_list *list)
{
	char		*cleft;
	t_list		*endnode;
	t_list		*remaindernode;
	int			i;
	int			k;

	i = 0;
	k = 0;
	remaindernode = malloc(sizeof(t_list));
	if (!remaindernode)
		return ;
	cleft = malloc(BUFFER_SIZE + 1);
	if (!cleft)
		return ;
	endnode = lastnode(list);
	while (endnode -> str[i] && endnode -> str[i] != '\n')
		i++;
	while (endnode -> str[i] && endnode -> str[++i])
		cleft[k++] = endnode -> str[i];
	cleft[k] = '\0';
	remaindernode -> str = cleft;
	remaindernode -> next = NULL;
	clean_list(&list, remaindernode, cleft);
}

static int	find_line(t_list *list)
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

static void	make_list(t_list **list, int fd)
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
		{
			free(buf);
			return ;
		}
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
	nextline = makestr(list);
	charsleft(list);
	return (nextline);
}
int main(void)
{
	const char *fd = "test.txt";
	int t = open(fd, O_RDONLY);
	char *result;
	result = get_next_line(t);
	printf("%s\n",result);
	printf("first is done\n");
	result = get_next_line(t);
	printf("%s\n",result);
	printf("second is done\n");
	// while ((result = get_next_line(t)) > 0)
	// {
	// 	printf("%s",result);
	// }
	close(t);
	return (0);
}