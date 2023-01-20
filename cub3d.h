/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:25:10 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 17:54:55 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include "tools/libft/libft.h"
# include "tools/libft/gnl/get_next_line.h"
# include "engine/minilibx/mlx.h"

# define BUTTON_W 13
# define BUTTON_A 0
# define BUTTON_S 1
# define BUTTON_D 2
# define BUTTON_LEFT 123
# define BUTTON_RIGHT 124
# define BUTTON_ESC 53
# define FOV 60.0
# define RADIAN 0.0174533
# define SIZE_BLOCK 60.0
# define SIZE_SPRITE 0.5
# define STEP 5
# define TURN 3

typedef struct	s_spr
{
	double		x;
	double		y;
	double		len;
	double		angle_ray;
	double		leg_x;
	double		leg_y;
	int			x_cell;
	int			y_cell;
}				t_spr;

typedef struct	s_rays
{
	int			image;
	int			type;
	double		len_h;
	double		len_v;
	double		offset_h;
	double		offset_v;
	double		angle_ray;
	double		angle_fish;
	double		angle_between;
	double		angle_right;
}				t_rays;

typedef struct	s_crd
{
	double		x;
	double		y;
	double		angle_direction;
	double		angle;
	double		step_y;
	double		step_x;
	int			sign_y;
	int			sign_x;
	double		beside_x;
	double		beside_y;
	int			field;
	double		correction;
	int			sign_direction;
}				t_crd;

typedef struct	s_texture
{
	char		*path;
	void		*image;
	int			*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			size_x;
	int			size_y;
}				t_texture;

typedef struct	s_mlx
{
	int			*addr;
	void		*mlx;
	void		*window;
	void		*image;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct	s_game
{
	t_texture	*texture[5];
	t_mlx		*mlx;
	t_crd		*crd;
	t_spr		*spr;
	int			*matrix_spr;
	int			*color_floor;
	int			*color_ceiling;
	int			size_x;
	int			size_y;
	int			size_map_y;
	int			size_map_x;
	char		**map;
	double		len_befor_pr;
	char		*line;
	int			count_spr;
	int			is_save;
	int			fd;
}				t_game;

void			run_game(t_game *data, int is_screen);
void			render(t_game *data, int is_screen);
void			load_image(t_game *data);
void			drawing_ceiling_floor(t_game *data);
void			drawing_walls(t_game *data, t_rays *rays);
void			drawing_sprts(t_game *data, t_rays *rays);
void			write_param_drawing(t_game *data, t_rays *rays);
void			draw_line(t_game *data, t_rays *rays, int i);
void			vertical_point(t_crd *crd);
void			horizontal_point(t_crd *crd);
void			init_sign(t_crd *crd, int type);
void			init_direction(t_crd *crd, double angle_ray);
void			vertical_ray(t_game *data, t_rays *rays);
void			horizontal_ray(t_game *data, t_rays *rays);
double			send_ray(t_game *data, t_rays *rays);
void			rounding(t_game *data, t_rays *rays, int *x, int *y);
void			first_len(t_game *data, double *len_x, double *len_y);
void			ft_free(void *pointer);
int				click_button(int key, t_game *data);
void			update_crd(t_game *data, double angle);
void			check_angle(double *angle);
int				check_grid(t_game *data, int x, int y);
void			parse_line(t_game *data, int code_gnl);
void			get_data_game(t_game *data);
t_game			*init_data_game(int is_save, int fd);
void			free_data_map(t_game *data);
void			rewriting_pointer(t_game **data, int count);
void			add_spr(t_game *data, int y, int x, int count_spr);
void			check_map(t_game *data);
void			check_point(t_game *data, int y, int x, int *count_point);
int				check_data(t_game *data, int code_test, int i, int k);
void			check_rgb(t_game *data, int **color, int count_comma, int flag);
void			handler_error(char *error, char *description, t_game *data);
int				ft_exit(t_game *data);
void			save_screen(t_game *data);
void			swap_data(t_game *data, int j);
void			sort_spr(t_game *data, int count);
void			update_rays(t_game *data, t_rays *rays);
void			write_len(t_game *data, t_rays *rays, int *is_horizontal);
double			percentage(double full, double part);
double			minus_if(int is_true, double one, double two);
void			init_matrix_spr(t_game *data);
char			*skipping(const char *s, int c);
double			ft_tan(double angle);
double			ft_cos(double angle);
double			ft_sin(double angle);

#endif
