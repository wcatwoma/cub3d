/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:42:57 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 14:34:44 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	get_texture(char **path, t_game *data, char *line)
{
	char	buf[0];
	int		fd;

	if (*path)
		handler_error("Error:\nduplicate key in map file!", data->line, data);
	if (!(*path = ft_strtrim(line, " \t")))
		handler_error(NULL, NULL, data);
	if (ft_strcmp(line + ft_strlen(line) - 4, ".xpm"))
		handler_error("Error:\nwrong extension file.xpm!", data->line, data);
	if (read((fd = open(*path, O_RDONLY)), buf, 0) == -1)
		handler_error(NULL, data->line, data);
	close(fd);
}

void	get_color(int **color, t_game *data, char *line)
{
	int		count_comma;
	int		flag;
	int		i;

	flag = 1;
	if (*color)
		handler_error("Error:\nduplicate key in map file!", data->line, data);
	i = 0;
	if (!(*color = (int*)ft_calloc(sizeof(int), 3)))
		handler_error(NULL, NULL, data);
	count_comma = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] == ',' && ++i && ++count_comma)
			continue;
		if ((!ft_isdigit(line[i]) && line[i] != ',') || count_comma > 2
			|| (count_comma < 2 && !line[i]))
			handler_error("Error:\nnot valid rgb code!", data->line, data);
		if (count_comma == 2 && (line[i] >= '0' && line[i] <= '9'))
			flag = 0;
		(*color)[count_comma] = line[i++] - '0' + (*color)[count_comma] * 10;
	}
	check_rgb(data, color, count_comma, flag);
}

void	get_size_screen(t_game *data, char *line)
{
	if (data->size_x != -1 || data->size_y != -1)
		handler_error("Error:\nduplicate key in map file!", data->line, data);
	data->size_x = 0;
	data->size_y = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	while (ft_isdigit(*line))
		data->size_x = *line++ - '0' + data->size_x * 10;
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line))
		handler_error("Error:\nnot valid size screen!", data->line, data);
	while (*line && ft_isdigit(*line))
		data->size_y = *line++ - '0' + data->size_y * 10;
	if (*line || (data->size_x <= 0 || data->size_y <= 0))
		handler_error("Error:\nnot valid size screen!", data->line, data);
}

void	get_map(t_game *data, char *line)
{
	int		count;

	count = 2;
	while (data->map && data->map[count - 1])
		count++;
	if (!data->map)
	{
		if (!(data->map = (char**)ft_calloc(sizeof(char*), count)))
			handler_error(NULL, NULL, data);
	}
	else
		rewriting_pointer(&data, ++count);
	if (!(data->map[count - 2] = ft_strdup(line)))
		handler_error(NULL, NULL, data);
	while (*line)
	{
		if (*line == '2')
			data->count_spr++;
		line++;
	}
}

void	parse_line(t_game *data, int code_gnl)
{
	if (code_gnl && !*data->line && data->map)
		handler_error("Error:\nNo valid map!", data->line, data);
	if (!ft_strncmp(data->line, "NO", 2) && !data->map)
		get_texture(&data->texture[0]->path, data, data->line + 2);
	else if (!ft_strncmp(data->line, "EA", 2) && !data->map)
		get_texture(&data->texture[1]->path, data, data->line + 2);
	else if (!ft_strncmp(data->line, "WE", 2) && !data->map)
		get_texture(&data->texture[2]->path, data, data->line + 2);
	else if (!ft_strncmp(data->line, "SO", 2) && !data->map)
		get_texture(&data->texture[3]->path, data, data->line + 2);
	else if (!ft_strncmp(data->line, "S", 1) && !data->map)
		get_texture(&data->texture[4]->path, data, data->line + 1);
	else if (!ft_strncmp(data->line, "F", 1) && !data->map)
		get_color(&data->color_floor, data, data->line + 1);
	else if (!ft_strncmp(data->line, "C", 1) && !data->map)
		get_color(&data->color_ceiling, data, data->line + 1);
	else if (!ft_strncmp(data->line, "R", 1) && !data->map)
		get_size_screen(data, data->line + 1);
	else if (ft_strchr(data->line, '1') || ft_strchr(data->line, '0'))
		get_map(data, data->line);
	else if ((code_gnl && !skipping(data->line, ' ') && data->map))
		return ;
	else if (data->line[0])
		handler_error("Error:\nfile is not filled in correctly!",
		data->line, data);
}
