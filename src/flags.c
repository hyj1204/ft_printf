/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 20:52:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/07/13 22:48:08 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ft_printf.h"

int		get_width_precision(const char *restrict *format, int *width, int *precision, va_list *ap)
//获得字符串内的最小显示宽度和精度
{
	int	num;
	int	more;

	num = 0;
	more = 0;
	if (ft_isdigit(**format))
	{
		while (ft_isdigit(**format)) //先看字符串内有没有数字，因为这个数字就是最小显示宽度
		{
			num = num * 10 + (**format - '0');  //如果是的话，就把字符转换成数字，然后看后一位
			(*format)++;
		}
	}
	else if (**format == '*')
	{
		num = va_arg(*ap, int);
		(*format)++;
	}

	if (num && (*width = num)) //如果最小显示宽度不为0，同时赋值给spec成功.more就是1，代表获得最小显示宽度数字成功
		more = 1;
	if (**format == '.') //如果字符串内有.的话
	{
		(*format)++;
		num = 0; //重置，重新使用这个数字
		if (ft_isdigit(**format))
		{
			while (ft_isdigit(**format))
			{
				num = num * 10 + (**format - '0');
				(*format)++;
			}
		}
		else if (**format == '*')
		{
			num = va_arg(*ap, int);
			(*format)++;
		}
		*precision = num; //获得精度数字.precision (-1的时候代表没有'.'),(0的时候代表有'.'，但是后面没有数字）
		more = 1;
	}
	return (more);
}

char	is_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int		get_flags(const char *restrict *format, char *flags) //*flags初始值是128个0
{
	int		more;

	more = 0;
	while (is_flag(**format)) //如果有#，0，-，空格，+，这个flags的话，more+1,并且
	{
		more = 1;
		flags[(int)**format] = 1; //把这个特征字符转换成int,在flags里对应的数字数组中设置1
		*format = *format + 1;  //移到后一个字符看是不是还是flags
	}
	return (more); //只要输入里面有flags的话就会返回1
}

int		print_a_arg(const char *restrict *format, va_list *ap, int (*dispatch[])(), t_spec *spec)
	//restrict用来保护指针不会指向同一个数据
	//输入的数据是“s/n"这种，从%后面一个字符开始。const char *restrict *format（*restrict *format所指的是char, restrict *format是一个不会指向相同地方的指针= “s/n"）
{
	char	conv;
	int		more;

	if (**format == '%')  //如果字符串里遇到%字符(即字符串里有%%)，标准库里的printf会自动忽略从可变参数中获得值，而是直接跳过第一个%，显示第一个%之后的字符（也是%开头）
	{

		ft_putchar(*(*format)++); //*format是%ss124（从第二次%开始）,这个等价于下面两条指令。1）显示**format（即第二个%）2）显示完之后把*format字符串的指针后移一位，即移到s上
		// ft_putchar(**format);
		// *format = *format + 1;
		return (1); //返回1表示成功显示1个字符（即%）
	}
	more = 1;
	while (more) //more > 0 时才继续执行。此时format在%之后一个位置，例如**format是s,通过这个s可以获得显示值的特性。
	{
		more = 0; //如果以下这些函数都没有返回值的话，说明%之后这个字符没有任何的数据类型可以对上，可以认为就是个普通字符
		more += get_flags(format, spec->flags); //获得字符串内的flags字符
		more += get_width_precision(format, &spec->width, &spec->precision, ap); //获得字符串内的最小显示宽度和精度
		more += get_len_modifier(format, spec->flags);  //因为length_modifier也是字符类型标示，所以也存在flags里
	} //more这个数字累加的值会显示一些特性
	if ((conv = get_conv_spec(format, spec->flags)) == 0)
	//conv = get_conv_spec(format, spec->flags） 先赋值，赋值成功显示1，失败显示0。
	//conv是s,c这种
	{
		if (**format)
			return (conv_single(spec, *(*format)++));
		return (0);
	}
	//因为%[flags][width][.precision][length]specifier是这个顺序，所有上面的代码也是按照这个顺序来的
	return (dispatch[(int)conv](ap, spec));//这个过程就是write出符合要求的字符
}