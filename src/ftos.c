/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:25:12 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long		power(int base, int exp)
{
	int		i;
	long	result;

	i = 1;
	if (exp == 0)
		return (0);
	result = base;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}

void		itoa_snip(char **str, int i, long long val)
{
	while (i)
	{
		(*str)[--i] = val % 10 + '0';
		val /= 10;
	}
}

int			fractional(char **str, long long fract, t_spec *spec)
{
	int		i;
	int		overflow;
	int		len;

	overflow = 0;
	i = spec->precision;
	len = d_len(fract);
	*str = (char *)ft_memalloc(sizeof(char) * (i + 1));
	if ((fract % 10) > 4) //如果最后一位大于4，则加10。因为fract存放是指定精度多一位的数字
		fract += 10;
	if (len < d_len(fract)) 
	//例如原来是99，+10之后变成了109，这里的1是需要进到整数部分的。所以这里要先做个标记。
		overflow = 1;
	fract /= 10; //恢复真实的指定精度
	itoa_snip(str, i, fract);//把小数部分的数字转变成字符串
	return (overflow);//0代表对整数部分没有进位，1代表对整数部分有进位
}

void		lftos(long double num, char **str, t_spec *spec)
{
	long long	whole;
	long long	fract;
	int			i;
	char		*new;
	char		*combined;

	if (!(num >= 0 && (spec->ispos = 1)))
		num = -num;
	i = 0;
	if (spec->precision == -1)
		spec->precision = 6;
	whole = (long long)num;
	num -= whole;
	fract = (long long)(power(10, spec->precision + 1) * num);
	whole += fractional(str, fract, spec);//fractional这里的返回1的话，就等于在整数部分+1.
	//这个函数也得到了小数部分的str
	if (spec->precision || spec->flags['#'])
		prefix(".", str);
	i = d_len(whole);//计算整数部分的长度
	new = (char *)ft_memalloc(sizeof(char) * (i + 1)); //分配整数部分的
	itoa_snip(&new, i, whole);
	combined = ft_strjoin(new, *str); //把整数部分和小数部分的字符串连接起来
	free(*str);
	free(new);
	*str = combined;
}

void		ftos(double num, char **str, t_spec *spec)
{
	long long   whole;
	long long	fract;
	int			i;
	char		*new;
	char		*combined;
		
	if (!(num >= 0 && (spec->ispos = 1)))
		num = -num;
	i = 0;
	if (spec->precision == -1)
		spec->precision = 6;
	whole = (long long)num; //例如：20.123456,whole就是20。
	//因为int的最大值是2147483647（10个数字），double最多可以准确显示14个数字。
	//所以用了long long转换（最大值9223372036854775807）
	num -= whole; //20.123456-20 = 0.123456 获得小数部分
	fract = (long long)(power(10, spec->precision + 1) * num); //这里会获得1234560,设置精度的后面一位
	whole += fractional(str, fract, spec); //frctional会做最后一位的四舍五入（rounded)
	if (spec->precision || spec->flags['#'])
		prefix(".", str);
	i = d_len(whole);
	new = (char *)ft_memalloc(sizeof(char) * (i + 1));
	itoa_snip(&new, i, whole);
	combined = ft_strjoin(new, *str);
	free(*str);
	free(new);
	*str = combined;
}
