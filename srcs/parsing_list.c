/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:40:48 by tsantoni          #+#    #+#             */
/*   Updated: 2020/04/21 10:31:55 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_char(t_scene *s, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		increment_elmts(s, 'p');
	else if (c == '2')
	{
		if (s->spr_nb > 50)
			exit_err_1(-15);
		create_sp(&s->sp[s->spr_nb]);
		s->spr_nb++;
	}
	else if (c != '0' && c != '1' && c != ' ')
		exit_err_1(-16);
}

int		get_clean_width(char *line)
{
	int	x;
	int	i;

	x = 0;
	i = -1;
	while (line[++i])
		if (line[i] == 'N' || line[i] == 'S' || line[i] == ' ' ||
				line[i] == 'W' || line[i] == 'E' ||
				line[i] == '0' || line[i] == '1' || line[i] == '2')
			x++;
	return (x);
}

char	*clean_line(char *line, t_scene *s)
{
	char	*cleaned;
	int		i;
	int		j;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	if (!(cleaned = malloc(sizeof(char) * get_clean_width(line) + 1)))
		exit_err_1(-12);
	while (line[i])
	{
		check_map_char(s, line[i]);
		cleaned[j++] = line[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

int		fill_list(t_scene *s, char *line)
{
	increment_elmts(s, 'm');
	if (count_elements(s) < 8)
		exit_err_1(-19);
	if (s->p->lst == NULL)
		s->p->lst = ft_lstnew(line);
	else
		ft_lstadd_back(&s->p->lst, ft_lstnew(line));
	return (OK);
}
