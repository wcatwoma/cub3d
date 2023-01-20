/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:58:52 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/23 15:10:09 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_data_game(t_game *data)
{
	int	code_gnl;

	while ((code_gnl = get_next_line(data->fd, &data->line)) > 0)
	{
		parse_line(data, code_gnl);
		ft_free(data->line);
		data->line = NULL;
	}
	if (code_gnl < 0)
		handler_error(NULL, NULL, data);
	parse_line(data, code_gnl);
	ft_free(data->line);
	data->line = NULL;
	data->spr = (t_spr*)malloc(sizeof(t_spr) * data->count_spr);
	if (!data->spr)
		handler_error(NULL, NULL, data);
}

int		main(int argc, char **argv)
{
	char	buf[0];
	t_game	*data;

	if (argc > 3 || argc < 2 || (argc == 3 && ft_strcmp(argv[2], "--save")) ||
		ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub"))
		handler_error("Error:\nwrong arguments!", NULL, NULL);
	data = init_data_game((argc == 3), open(argv[1], O_RDONLY));
	if (read(data->fd, buf, 0) < 0)
		handler_error(NULL, NULL, data);
	get_data_game(data);
	if (check_data(data, 1, 0, 0))
		handler_error("Error:\nnot all input ​​are provided!", NULL, data);
	check_map(data);
	run_game(data, (argc == 3));
	return (0);
}
