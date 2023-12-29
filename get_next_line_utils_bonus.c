/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:25:45 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/28 18:02:33 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
				return ;
			}
			full_line[k++] = list->str[i++];
		}
		list = list->next;
	}
	full_line[k] = '\0';
}

t_list	*last_node(t_list *list)
{
	while (list != NULL)
	{
		if (list -> next == NULL)
			return (list);
		list = list -> next;
	}
	return (list);
}

int	add_node(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (-1);
	last = last_node(list[fd]);
	if (last == NULL)
		list[fd] = new_node;
	else
		last->next = new_node;
	new_node -> str = buf;
	new_node -> next = NULL;
	return (0);
}

int	len_of_string(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	clean_list(t_list **list, t_list *remainder_node)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	tmp = *list;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	if (remainder_node == 0)
		return ;
	if (remainder_node->str[0])
		*list = remainder_node;
	else
	{
		free(remainder_node->str);
		free(remainder_node);
	}
}
