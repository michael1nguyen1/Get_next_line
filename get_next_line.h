/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 20:52:03 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/23 20:52:04 by linhnguy         ###   ########.fr       */
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

void	copy_str(t_list *list, char *full_line);

char	*get_next_line(int fd);

t_list	*last_node(t_list *list);

void	add_node(t_list **list, char *buf);

int		len_of_string(t_list *list);

void	clean_list(t_list **list, t_list *remainder_node);

#endif
