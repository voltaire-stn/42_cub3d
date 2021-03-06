/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:14:25 by tsantoni          #+#    #+#             */
/*   Updated: 2019/10/18 13:11:20 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isset(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*res;

	begin = 0;
	while (s1[begin] && ft_isset(s1[begin], (char *)set) == 1)
		begin++;
	end = ft_strlen(s1) - 1;
	if (end - begin <= 0)
	{
		if (!(res = malloc(sizeof(char) * 1)))
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	while (s1[end] && ft_isset(s1[end], (char *)set) == 1)
		end--;
	if (!(res = ft_substr(s1, begin, (end - begin + 1))))
		return (NULL);
	return (res);
}
