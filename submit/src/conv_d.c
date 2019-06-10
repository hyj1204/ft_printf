/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:23:18 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 17:07:17 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

void		precision_d(char **str, t_spec *spec)
{
	char	*new;
	int		len;
	int		pad_len;
	int		i;
	char	*padding;

	len = ft_strlen(*str);
	if (spec->precision != -1 && (pad_len = spec->precision - len) > 0)
	{
		padding = (char *)ft_memalloc(sizeof(char) * (pad_len + 1));
		i = 0;
		while (i < pad_len)
			padding[i++] = '0';
		new = ft_strjoin(padding, *str);
		free(*str);
		free(padding);
		*str = new;
	}
	else if (spec->precision == 0 && spec->iszero)
	{
		free(*str);
		*str = (char *)ft_memalloc(sizeof(char) * 1);
	}
	prefix_octal(str, spec);
}

void		width_d_2(char **str, t_spec *spec, t_width_d v)
{
	int		i;

	i = 0;
	while (i < v.pad_len)
		v.padding[i++] = v.c;
	if (spec->flags['-'])
		v.new = ft_strjoin(*str, v.padding);
	else if (v.c == '0')
		v.new = ft_strjoin(v.padding, *str);
	else
	{
		prefix_sign(str, spec);
		v.new = ft_strjoin(v.padding, *str);
	}
	free(*str);
	free(v.padding);
	*str = v.new;
	if (spec->flags['-'] || v.c == '0')
		prefix_sign(str, spec);
}

void		width_d(char **str, t_spec *spec)
{
	t_width_d	v;

	v.len = ft_strlen(*str);
	if (spec->width != -1 && (v.pad_len = spec->width - v.len) > 0)
	{
		if (!spec->isunsigned && (!spec->ispos || spec->flags[' '] || \
					spec->flags['+']))
			v.pad_len--;
		else if (spec->flags['#'] && (spec->flags['x'] || spec->flags['X']))
			v.pad_len -= 2;
		v.padding = (char *)ft_memalloc(sizeof(char) * (v.pad_len + 1));
		v.c = ' ';
		if ((spec->precision == -1 || spec->flags['f'] || spec->flags['F']) \
		&& !spec->flags['-'] && spec->flags['0'])
			v.c = '0';
		width_d_2(str, spec, v);
	}
	else
		prefix_sign(str, spec);
}

int			conv_d(va_list *ap, t_spec *spec)
{
	int					len;
	char				*str;
	unsigned long long	num_ull;
	long long			num;

	num_ull = len_mod(ap, spec);
	num = (long long)num_ull;
	if (num <= -128 && spec->flags['h'] == 2 && spec->flags['l'] == 1)
		num = 128;
	if (num == 0)
		spec->iszero = 1;
	if (num_ull == -9223372036854775808ULL)
		str = ft_strdup("9223372036854775808");
	else
		itoa_d(num, &str, spec);
	precision_d(&str, spec);
	width_d(&str, spec);
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
