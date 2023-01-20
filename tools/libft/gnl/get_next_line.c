/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 13:43:36 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/07 10:39:31 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_end_of_line(char **end_line, char *buf, char **tail)
{
	if (!buf)
		return (1);
	if ((*end_line = ft_strchr(buf, '\n')) != NULL)
	{
		**end_line = '\0';
		if (!(*tail = ft_strdup(*end_line + 1)))
			return (-1);
	}
	return (1);
}

int		check_tail(char **line, char **tail, char **end_line)
{
	char		*start_tail;
	int			option;

	start_tail = *tail;
	if (get_end_of_line(end_line, start_tail, tail) == -1)
		return (-1);
	if (start_tail != *tail)
		*line = ft_strdup(start_tail);
	else
		*line = ft_strdup(*tail ? *tail : "");
	if (!(*line))
		return (-1);
	option = start_tail != *tail ? 1 : 0;
	free(option ? start_tail : *tail);
	if (option)
		start_tail = NULL;
	else
		*tail = NULL;
	return (1);
}

int		get_line(int fd, char **line, char **tail)
{
	char		buf[BUFFER_SIZE + 1];
	char		*end_line;
	char		*tmp;
	size_t		size;

	end_line = NULL;
	size = 1;
	if (check_tail(line, tail, &end_line) == -1 || (read(fd, buf, 0) == -1))
		return (-1);
	while (!end_line && (size = read(fd, buf, BUFFER_SIZE)))
	{
		buf[size] = '\0';
		tmp = *line;
		if (get_end_of_line(&end_line, buf, tail) == -1
			|| !(*line = ft_strjoin(*line, buf)))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	return (end_line ? 1 : 0);
}

t_file	*search_node(int fd, t_file *tmp, t_file **befor_node)
{
	while (tmp)
	{
		if (tmp && tmp->fd == fd)
			break ;
		if (!(tmp->next))
			if (!(tmp->next = ft_lstnew(fd)))
				return (NULL);
		*befor_node = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static t_file	*files;
	t_file			*tmp;
	t_file			*befor_node;
	int				res;

	if (fd < 0 || !line || !(files = files ? files : ft_lstnew(fd)))
		return (-1);
	befor_node = NULL;
	if (!(tmp = search_node(fd, files, &befor_node)))
		return (-1);
	res = get_line(tmp->fd, line, &tmp->tail);
	if (befor_node != NULL && (!res || res == -1))
	{
		befor_node->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	else if (!res || res == -1)
	{
		tmp = files;
		files = files->next;
		free(tmp);
	}
	return (res);
}
