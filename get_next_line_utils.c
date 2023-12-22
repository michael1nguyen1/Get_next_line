/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:26 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/22 22:20:51 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lastnode(t_list *list)
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
	t_list	*newnode;
	t_list	*last;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return ;
	last = lastnode(*list);
	newnode -> str = buf;
	if (last == NULL)
		*list = newnode;
	else
		last->next = newnode;
	newnode -> next = NULL;
}

int	lenofstring(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list)
	{
		i = 0;
		while (list -> str[i] && list -> str[i] != '\n')
		{
			if(list->str[i] == '\n')
			{
				++len;
				return (len);
			}
			i++;
			len++;
		}
		list = list -> next;
	}
	return (len);
}

void	clean_list(t_list **list, t_list *remaindernode, char *cleft)
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
		if (remaindernode->str[0])
			*list = remaindernode;
	else
	{
		free(remaindernode);
		free(cleft);
	}
}