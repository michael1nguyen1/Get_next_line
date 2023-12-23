/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:12:00 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/23 20:51:03 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*make_str(t_list *list)
{
	char	*full_line;
	int		strlen;

	strlen = (len_of_string(list));
	full_line = malloc(strlen +1);
	if (!full_line)
		return (NULL);
	copy_str(list, full_line);
	return (full_line);
}

static void	chars_left(t_list **list)
{
	char		*c_left;
	t_list		*end_node;
	t_list		*remainder_node;
	int			i;
	int			k;

	i = 0;
	k = 0;
	remainder_node = malloc(sizeof(t_list));
	if (!remainder_node)
		return ;
	c_left = malloc(BUFFER_SIZE + 1);
	if (!c_left)
		return ;
	end_node = last_node(*list);
	while (end_node->str[i] && end_node->str[i] != '\n')
		i++;
	while (end_node->str[i] && end_node->str[++i])
		c_left[k++] = end_node->str[i];
	c_left[k] = '\0';
	remainder_node->str = c_left;
	remainder_node->next = NULL;
	clean_list(list, remainder_node);
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
		add_node(list, buf);
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
	nextline = make_str(list);
	chars_left(&list);
	return (nextline);
}
// int main(void)
// {
//     int    fd;
//     char    *line;

//     fd = open("test.txt", O_RDONLY);
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//     }
// // line = get_next_line(fd);
// // 	printf("%s\n",line);
// // 	printf("first is done\n");
// // 	line = get_next_line(fd);
// // 	printf("%s\n",line);
// // 	printf("second is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// }