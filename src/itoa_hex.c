/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:28 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:25:31 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

static void	itoa_hex_str(unsigned long vp_num, char **str, int len, \
		t_spec *spec)
{
	char	c;
	int		i;

	c = 'a'; //默认字母是小写
	if (spec->flags['X']) //如果输入flags是大写的话，字母就是大写
		c = 'A';
	while (len > 0)
	{
		len--; //倒着的得出str
		i = vp_num % 16;   //i是余数，例如f的余数就是15
		if (i < 10)
			(*str)[len] = i + '0';
		else
			(*str)[len] = i - 10 + c;
		vp_num /= 16; //除以16之后看后一个余数
	}
}

static int	itoa_hex_len(unsigned long vp_num)
{
	int		len;

	len = 0;
	// if (vp_num == 0x0) //特殊情况，如果是指向0的时候，不返回任何0x后面的数
	// 	return 0;
	while ((vp_num /= 16))//每一位都是16进位，所以除以16能得到需要显示多少位。例如：当是f的时候，f/16是0，+1之后是1位
		len++;
	return (len + 1);
}

void		itoa_hex(unsigned long vp_num, char **str, t_spec *spec)
{
	int		len;
	

	len = itoa_hex_len(vp_num); //获得地址的显示的长度,这里的长度不包括0x
	// printf("len = %d",len);
	*str = (char *)ft_memalloc(sizeof(char) * (len + 1));//分配显示地址所需的字符长度
	itoa_hex_str(vp_num, str, len, spec);//这个函数会把这个地址的字符串给str指针指向的内容
	}
