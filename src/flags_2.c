/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:24:47 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:24:49 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	is_conv_spec(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || \
			c == 'i' || c == 'o' || c == 'u' || \
			c == 'x' || c == 'X' || c == 'f' || c == 'F')
		return (1);
	return (0);
}

char	get_conv_spec(const char *restrict *format, char *flags)
{
	if (is_conv_spec(**format)) //判断**format是d,s这种类型的char的吗？是的话就把flags数组里的对应的，例如flags[(int) 's'把char变为int数字] =1
	{
		flags[(int)**format] = 1;
		return (*(*format)++);
	}
	return (0);
}

char	is_len_mod(char c)
{
	if (c == 'h' || c == 'l' || c == 'L')
		return (1);
	return (0);
}

int		get_len_modifier(const char *restrict *format, char *flags)//获得hh,h,l,ll,L这种，把char，short(int)等转换成各进制
{
	int		more;

	more = 0;
	while (is_len_mod(**format))
	{
		more = 1;
		if (**format == *((*format) + 1))//如果遇到h,l这种之后还有hl的话，就设置2，代表有两个h或者l
		{
			flags[(int)**format] = 2;
			*format += 2;
		}
		else
		{
			flags[(int)**format] = 1;
			*format += 1;
		}
	}
	return (more);
}
