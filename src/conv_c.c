/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:22:59 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:23:09 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		conv_c(va_list *ap, t_spec *spec) 
{
	char	*str;
	int		len;

	str = (char *)ft_memalloc(sizeof(char) * 2); //str只有两个字节，一个放要显示的char,一个放\0
	str[0] = va_arg(*ap, int); //输入的单个字符'a'在系统里存的是int(对应的机器码)，所以第一个放的是char的机器码
	if (str[0] == 0) //如果机器码是0,即指向null
	{
		spec->isnull = 1; //则把种类设置成null
		spec->width = spec->width != -1 ? spec->width - 1 : -1;
		//如果最小显示宽度不等于-1，则宽度减1，因为显示了一个字符
		//如果宽度等于-1就不变，因为已经超出了最小显示范围（等于忽略最小显示位）
	}
	width_s(&str, spec); //处理字符宽度（_s是仅适用于char和str的宽度处理），没到最小字符数的话，就用相应的字符填充。
	len = ft_strlen(str) + spec->isnull; //成功打印的字符数是返回新字符串的长度+spec->isnull(如果是null字符的话就是1，不是的话就是0)
	ft_putstr(str);//显示新字符串（已经处理过最小宽度）
	free(str);
	if (spec->isnull)
		ft_putchar(0); //显示机器码0对应的字符
	return (len);
}
