/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:24:12 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:24:15 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			conv_u(va_list *ap, t_spec *spec)
{
	int			len;
	char		*str;
	long long	num;

	spec->isunsigned = 1; //输入是unsigned的
	num = lenmod_unsigned(ap, spec); 
	//获得各类型的输入数字,都是unsigned的，最多就是unsigned long long
	if (num == 0)
		spec->iszero = 1;
	itoa_u(num, &str); //把输入的数字（unsigned long long)转换成无符号字符,给str
	precision_d(&str, spec); //获得精度，实际要显示多少个数字，共用函数
	width_d(&str, spec); //共用函数
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
