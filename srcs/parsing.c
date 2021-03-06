/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:22:14 by tsantoni          #+#    #+#             */
/*   Updated: 2020/04/22 16:29:29 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(t_scene *s, char *line, int *i, char c)
{
	skip_space(line, i);
	(*i)++;
	skip_space(line, i);
	if (!line[*i])
		exit_err_1(-9);
	s->rgb->r = ft_atoi_ptr(line, i);
	skip_space_char(line, i, ',');
	s->rgb->g = ft_atoi_ptr(line, i);
	skip_space_char(line, i, ',');
	s->rgb->b = ft_atoi_ptr(line, i);
	skip_space(line, i);
	if (*i != (int)ft_strlen(line) || check_range(s->rgb->r, 0, 255) == 0 ||
			check_range(s->rgb->g, 0, 255) == 0 ||
			check_range(s->rgb->b, 0, 255) == 0)
		exit_err_1(-9);
	if (c == 'C')
		s->col->c = convert_color(s->rgb->r, s->rgb->g, s->rgb->b);
	if (c == 'F')
		s->col->f = convert_color(s->rgb->r, s->rgb->g, s->rgb->b);
	increment_elmts(s, c);
}

void	parse_res(t_scene *s, char *line, int *i)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	skip_space(line, i);
	(*i)++;
	skip_space(line, i);
	if (!line[*i])
		exit_err_1(-8);
	s->mlx->win->x = ft_atoi_ptr(line, i);
	skip_space(line, i);
	s->mlx->win->y = ft_atoi_ptr(line, i);
	skip_space(line, i);
	if (*i != (int)ft_strlen(line))
		exit_err_1(-8);
	mlx_get_screen_size(s->mlx->ptr, &x, &y);
	ft_max(&s->mlx->win->x, x);
	ft_max(&s->mlx->win->y, y);
	ft_min(&s->mlx->win->x, 26);
	ft_min(&s->mlx->win->y, 26);
	increment_elmts(s, 'R');
}

void	dispatch_non_map(t_scene *s, char *line, int *i)
{
	if (line[*i] == 'R')
		parse_res(s, line, i);
	else if (line[*i] == 'C')
		parse_color(s, line, i, 'C');
	else if (line[*i] == 'F')
		parse_color(s, line, i, 'F');
	else if (line[*i] == 'N' && line[*i + 1] == 'O')
		parse_texture(s, line, i, 'N');
	else if (line[*i] == 'S' && line[*i + 1] == 'O')
		parse_texture(s, line, i, 'S');
	else if (line[*i] == 'W' && line[*i + 1] == 'E')
		parse_texture(s, line, i, 'W');
	else if (line[*i] == 'E' && line[*i + 1] == 'A')
		parse_texture(s, line, i, 'E');
	else if (line[*i] == 'S')
		parse_texture(s, line, i, 's');
	else if (*i != (int)ft_strlen(line))
		exit_err_1(-18);
}

void	dispatch_parsing(t_scene *s, char *line, int *i)
{
	*i = 0;
	skip_space(line, i);
	if (line[*i] == '1' || line[*i] == '0' || line[*i] == '2')
		fill_list(s, clean_line(line, s));
	else
	{
		if (s->elmts[9] != 0)
			exit_err_1(-20);
		dispatch_non_map(s, line, i);
	}
}

void	parsing(t_scene *s, int fd)
{
	int		gnl;
	char	*line;
	int		*i;

	if (!(i = malloc(sizeof(int))))
		exit_err_1(-12);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		dispatch_parsing(s, line, i);
		free(line);
	}
	free(i);
	if (gnl == 0)
		free(line);
	if (gnl == -1)
		exit_err_1(2);
	check_elements(s);
	if (!(s->zbuf = malloc(sizeof(double) * s->mlx->win->x)))
		exit_err_1(-12);
	fill_map(s);
	init_pos_on_map(s);
	copy_map(s);
	if (check_map(s, s->pos->x + 0.5, s->pos->y + 0.5) == 0)
		exit_err_1(-17);
}
