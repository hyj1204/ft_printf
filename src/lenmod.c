/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:55 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:25:57 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long long			len_mod(va_list *ap, t_spec *spec) //针对长度转换功能，把各类型的输入转换成各进制的数字显示出来
{
	long long			num;

	if (spec->flags['l'] == 2)    //如果有modifier的话，获取输入中相应type的数字
		num = va_arg(*ap, long long);
	else if (spec->flags['l'] == 1)
		num = va_arg(*ap, long);
	else if (spec->flags['h'] == 2)
		num = (signed char)va_arg(*ap, int);
	else if (spec->flags['h'] == 1)
		num = (short)va_arg(*ap, int);
	else
		num = va_arg(*ap, int);
	return (num);
}

unsigned long long	lenmod_unsigned(va_list *ap, t_spec *spec)
//通过unsigned的modifier，获得实际的数字
{
	unsigned long long	num;

	if (spec->flags['l'] == 2)
		num = va_arg(*ap, unsigned long long);
	else if (spec->flags['l'] == 1)
		num = va_arg(*ap, unsigned long);
	else if (spec->flags['h'] == 2)
		num = (unsigned char)va_arg(*ap, unsigned int);
	else if (spec->flags['h'] == 1)
		num = (unsigned short)va_arg(*ap, unsigned int);
	else
		num = va_arg(*ap, unsigned int);
	return (num);
}

