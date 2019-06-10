/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:46 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/08 18:59:13 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void		itoa_u_str(unsigned long long num, char **str, int len)
{
	while (len > 0)
	{
		len--;
		(*str)[len] = num % 10 + '0';
		num /= 10;
	}
}

int			itoa_u_len(unsigned long long num)
{
	int		len;

	len = 0;
	while ((num /= 10))
		len++;
	return (len + 1);
}

void		itoa_u(unsigned long long num, char **str)
{
	int		len;

	len = itoa_u_len(num);
	*str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	itoa_u_str(num, str, len);
}
