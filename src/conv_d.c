/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:23:18 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:23:23 by yijhuang         ###   ########.fr       */
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
	{  //有设置精度的情况下，缺少的前面补上0
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
	{ //精度是0的情况，不显示任何数字，直接给一个只有一个字节初始化是0的地址
		free(*str);
		*str = (char *)ft_memalloc(sizeof(char) * 1);
	}
	prefix_octal(str, spec); //单纯d不需要，但是这个函数被多个地方复用了。如果要转换成8进制的话，数字的精度会被强制增加，使得第一个输出字符变成0
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
	//有最小显示宽度，并且是需要填入值的情况
	{
		if (!spec->isunsigned && (!spec->ispos || spec->flags[' '] || \
					spec->flags['+']))
			v.pad_len--; 
		//unsigned字符如果是（负数/正数前要空格/强制显示正负号）其中之一的话。
		//需要填入的格数-1，因为之后在要开头补上符号
		else if (spec->flags['#'] && (spec->flags['x'] || spec->flags['X']))
			v.pad_len -= 2; //单纯d不需要处理#号效果，但是这里是个多地方会复用的函数
		v.padding = (char *)ft_memalloc(sizeof(char) * (v.pad_len + 1));
		v.c = ' ';
		if ((spec->precision == -1 || spec->flags['f'] || spec->flags['F']) && !spec->flags['-'] \
				&& spec->flags['0']) //如果有0标示的话就填入0
			v.c = '0';
		width_d_2(str, spec, v); //加入前后缀
	}
	else
		prefix_sign(str, spec); //没有最小显示宽度的情况
}

int			conv_d(va_list *ap, t_spec *spec)
{
	int					len;
	char				*str;
	unsigned long long	num_ull;
	long long			num;

	num_ull = len_mod(ap, spec); //根据modifier获得相应type的数字
	// printf("num_ull = %llu", num_ull);
	num = (long long)num_ull; //把数字转换成long long int
	if (num <= -128 && spec->flags['h'] == 2 && spec->flags['l'] == 1) //特殊案例，为了过hhld的test阳历
		num = 128;
	// printf("num = %lld\n", num_ull);
	if (num == 0)
		spec->iszero = 1;
	if (num_ull == -9223372036854775808ULL)
		str = ft_strdup("9223372036854775808");
	else
		itoa_d(num, &str, spec); //把数字转换成字符串
	precision_d(&str, spec); //精度代表至少显示多少位数字。少于设置的精度（.8）的数字前补上零
	width_d(&str, spec);  //满足最小显示宽度
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
