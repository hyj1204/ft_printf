/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:28 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/08 18:58:17 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

static void	itoa_hex_str(unsigned long vp_num, char **str, int len, \
		t_spec *spec)
{
	char	c;
	int		i;

	c = 'a';
	if (spec->flags['X'])
		c = 'A';
	while (len > 0)
	{
		len--;
		i = vp_num % 16;
		if (i < 10)
			(*str)[len] = i + '0';
		else
			(*str)[len] = i - 10 + c;
		vp_num /= 16;
	}
}

static int	itoa_hex_len(unsigned long vp_num)
{
	int		len;

	len = 0;
	while ((vp_num /= 16))
		len++;
	return (len + 1);
}

void		itoa_hex(unsigned long vp_num, char **str, t_spec *spec)
{
	int		len;

	len = itoa_hex_len(vp_num);
	*str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	itoa_hex_str(vp_num, str, len, spec);
}
