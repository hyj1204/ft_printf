/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:18 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/08 18:56:23 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void		itoa_str(long long num, char **str, int len)
{
	while (len > 0)
	{
		(*str)[--len] = num % 10 + '0';
		num /= 10;
	}
}

int			itoa_len(long long num)
{
	int		len;

	len = 0;
	while ((num /= 10))
		len++;
	return (++len);
}

void		itoa_d(long long num, char **str, t_spec *spec)
{
	int		len;

	if (num >= 0)
		spec->ispos = 1;
	else
		num = -num;
	len = itoa_len(num);
	*str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	itoa_str(num, str, len);
}
