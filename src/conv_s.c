/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 22:38:43 by yijhuang          #+#    #+#             */
/*   Updated: 2019/05/30 19:51:13 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	precision_s(char **str, t_spec *spec)
{
	char	*new;
	int		i;

	if (spec->precision == -1) //如果没设置精度（-1）是初始化的值，则跳过不处理
		return ;
	if (ft_strlen(*str) > (size_t)spec->precision)//如果str的长度大于精度的话就要减去一些值。
	{
		new = (char *)ft_memalloc(spec->precision + 1);
		i = 0;
		while (i < spec->precision)
		{			
			new[i] = (*str)[i];
			i++;
		}
		free(*str); //把原来的str free掉
		*str = new; //把新的修剪过的字符串给str用于显示
	}
}

char	*width_s_2(int pad_len, char *padding, char c) //输入空格长度，填入位置地址，填入字符
{
	int		i;

	i = 0;
	while (i < pad_len)
	{
		padding[i] = c; //从填入起始位置开始每一个都填入（输入字符）
		i++;
	}
	return (padding);//返回已填好的字符串
}

void	width_s(char **str, t_spec *spec) //输入一个字符串，处理之后返回一个新字符串
{
	int		len;
	char	*padding;
	char	*newstr;
	int		pad_len;

	if (spec->width == -1 || spec->width <= (len = ft_strlen(*str)))
		return ; //如果width=-1或者输入的字符串大小大于最小输出宽度，则忽略这个题条件
	pad_len = spec->width - len;  //否则的话填入的大小等于设置大小-实际大小
	padding = (char *)ft_memalloc(pad_len + 1);//给需要填入的内容分配内存
	if (spec->flags['-'])  //如果是负号开头的（左对齐），在字符串后面填入空格
		newstr = ft_strjoin(*str, width_s_2(pad_len, padding, ' '));
	else if (spec->flags['0']) //如果是0号开头的，填入0。在字符串前面加上0
		newstr = ft_strjoin(width_s_2(pad_len, padding, '0'), *str);
	else //或者就是在字符串前面加上空格
		newstr = ft_strjoin(width_s_2(pad_len, padding, ' '), *str);
	free(padding);
	free(*str);
	*str = newstr;
}

int		conv_s(va_list *ap, t_spec *spec)
{
	char	*str;
	int		len;

	if ((str = va_arg(*ap, char *)))//如果输入参数的地址存在（不为null),则str指针指向该地址
		str = ft_strdup(str); //为此创建一个新内存的str
	else
		str = ft_strdup("(null)");
	precision_s(&str, spec);//把字符串放进处理精度（最多显示多少个字符），处理之后str会剪掉多出来的字符
	width_s(&str, spec);//处理显示的宽度（左右空间对其/填空格）
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}