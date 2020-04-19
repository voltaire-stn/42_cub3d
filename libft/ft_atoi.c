/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:18:33 by tsantoni          #+#    #+#             */
/*   Updated: 2020/04/19 14:36:30 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char const *s)
{
	int i;
	int n;
	int res;

	i = 0;
	res = 0;
	n = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			n = n * -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res * n);
}
