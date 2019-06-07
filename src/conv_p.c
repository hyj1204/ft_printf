/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:23:50 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:23:53 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

void	precision_p(char **str, t_spec *spec)
{
	int		i;
	int		len;
	int		pad_len;
	char	*padding;
	char	*new;

	len = ft_strlen(*str);
	// if (spec->precision == 0)
	// {
	// 	*str[2] = '\0';
	// 	return;
	// }
	if (spec->precision == -1 || spec->precision < len)
		return ;
	pad_len = spec->precision - len;
	padding = (char *)ft_memalloc(sizeof(char) * (pad_len + 1));
	i = -1;
	while (++i < pad_len)
		padding[i] = '0'; //位数不够指定精度的时候在数字之前填充0
	new = ft_strjoin(padding, *str);
	free(padding);
	free(*str);
	*str = new;
}

void	prefix_0x(char **str)
{
	char	*new;

	new = ft_strjoin("0x", *str);
	free(*str);
	*str = new;
}

void	width_p_2(char **str, t_width_d v) //注意这里是p_2，函数里的是s_2
{
	prefix_0x(str); 
	v.new = ft_strjoin(width_s_2(v.pad_len, v.padding, ' '), *str);
	free(v.padding);
	free(*str);
	*str = v.new;
}

void	width_p(char **str, t_spec *spec)
{
	t_width_d	v;

	if (spec->width == -1 || spec->width <= (v.len = ft_strlen(*str)) + 2)
	//这一步里同时个v.len赋值了.设置的最小宽度小于等于 字符串 + 2（ox) 时，条件失效，直接+0x返回
	{
		prefix_0x(str);  //在字符串前加上0x
		return ;
	}
	v.pad_len = spec->width - (v.len + 2);  //设置需要填充的宽度是设置的宽度-数字长-2（0x的宽度）
	v.padding = (char *)ft_memalloc(v.pad_len + 1); //分配填充的空间
	if (spec->flags['-']) //如果flag里面对应-的数字格里是1的话，就是左对齐
		v.new = ft_strjoin(*str, width_s_2(v.pad_len, v.padding, ' '));
	else if (spec->flags['0'] && spec->precision == -1) //有0标志符并且没有精度的情况下，用0填充
		v.new = ft_strjoin(width_s_2(v.pad_len, v.padding, '0'), *str);
	else
	{
		width_p_2(str, v); 
		//处理point的最小宽度，这个最小宽度里包含了0x,此时输入的str未包含0x
		//v里面已经有了需要填充的宽度pad_len和空间padding
		return ;
	}
	prefix_0x(&v.new);
	free(v.padding);
	free(*str);
	*str = v.new;
}

int		conv_p(va_list *ap, t_spec *spec)
{
	char	*str; //建一个str用来放实际显示出来的字符串
	int		len;
	void	*vp;

	vp = va_arg(*ap, void *); //获得可变参数中的地址，此时vp就是0x7ffee566a940类似这样的一个地址
	itoa_hex((unsigned long)vp, &str, spec);
	//因为地址的长度很长，所以先用unsigned long转换一下，注意此时的vp就是一串数字。
	//这个函数就是把输入参数vp数字，转换成字符串（str所指的内容）
	if (vp == 0 && spec->precision == 0)  //为了实现printf("%10p, %.p\n", 0, 0)有精度点点的时候，0x后面没数字。
		*str = '\0';
	precision_p(&str, spec); //先把得到的字符串处理下精度，不够精度的前面填充0,超过的忽略
	width_p(&str, spec); //处理最小显示宽度
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
