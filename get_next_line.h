/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:16:53 by linhnguy          #+#    #+#             */
/*   Updated: 2023/12/28 18:16:50 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

void	copy_str(t_list *list, char *full_line);

char	*get_next_line(int fd);

t_list	*last_node(t_list *list);

int		add_node(t_list **list, char *buf);

int		len_of_string(t_list *list);

void	clean_list(t_list **list, t_list *remainder_node);

#endif
