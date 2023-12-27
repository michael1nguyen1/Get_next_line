/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:20:35 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/27 19:26:52 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

static char	*make_str(t_list *list)
{
	char	*full_line;
	int		strlen;

	strlen = (len_of_string(list));
	full_line = malloc(strlen + 1);
	if (!full_line)
		return (NULL);
	copy_str(list, full_line);
	return (full_line);
}

int	chars_left(t_list **list)
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
		return (-1);
	c_left = malloc(BUFFER_SIZE + 1);
	if (!c_left)
		return (free(remainder_node), -1);
	end_node = last_node(*list);
	while (end_node->str[i] && end_node->str[i] != '\n')
		i++;
	while (end_node->str[i] && end_node->str[++i])
		c_left[k++] = end_node->str[i];
	c_left[k] = '\0';
	remainder_node->str = c_left;
	remainder_node->next = NULL;
	clean_list(list, remainder_node);
	return (0);
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

int	make_list(t_list **list, int fd)
{
	int			buff_read;
	char		*buf;
	int			tmp;

	while (!find_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (-1);
		buff_read = read(fd, buf, BUFFER_SIZE);
		if (buff_read == -1)
			return (free(buf), -1);
		if (buff_read == 0)
			return (free(buf), 0);
		buf[buff_read] = '\0';
		tmp = add_node(list, buf);
		if (tmp == -1)
			return (free(buf), -1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				tmp;

	if (fd < 0 || BUFFER_SIZE < 0 || read (fd, &next_line, 0) < 0)
	{
		if (list != NULL)
			clean_list(&list, 0);
		return (NULL);
	}
	tmp = make_list(&list, fd);
	if (tmp == -1 || !list)
		return (clean_list(&list, 0), NULL);
	next_line = make_str(list);
	if (next_line == NULL)
		return (clean_list(&list, 0), NULL);
	tmp = chars_left(&list);
	if (tmp == -1)
		return (free(next_line), clean_list(&list, 0), NULL);
	return (next_line);
}
// int main(void)
// {
//     int    fd;
//     char    *line;

//     fd = open("test.txt", O_RDONLY);
// // line = get_next_line(fd);
// // 	printf("%s\n",line);
// // 	printf("first is done\n");
// // 	line = get_next_line(fd);
// // 	printf("%s\n",line);
// // 	printf("second is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
// // 	printf("%s\n",line);
// // 	printf("third is done\n");
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
// 	free(line);
//     }
// }