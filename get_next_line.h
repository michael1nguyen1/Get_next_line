/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:16:53 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/22 22:20:22 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

t_list	*lastnode(t_list *list);

void	addnode(t_list **list, char *buf);

int		lenofstring(t_list *list);

void	clean_list(t_list **list, t_list *remaindernode, char *cleft);

#endif
