/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:12:12 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/06 21:32:08 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"


//dispatch派遣函数，输入是一个指针指向一组函数指针数组，数组中的每一个都指向一个函数
//函数指针数组中的每个值dispatch[*]指向对应的转换函数
//所以经过这个函数处理之后，dip
void	init_dispatch(int (*dispatch[])()) 
{
	dispatch['s'] = conv_s;
	dispatch['c'] = conv_c;
	dispatch['p'] = conv_p;
	dispatch['d'] = conv_d;
	dispatch['i'] = conv_d;
	dispatch['u'] = conv_u;
	dispatch['o'] = conv_o;
	dispatch['x'] = conv_x;
	dispatch['X'] = conv_x;
	dispatch['f'] = conv_f;
	dispatch['F'] = conv_f;
}

void	init_spec(t_spec *spec)   //输入是一个指针spec,指向的内容是t_spec结构，给输入指针所指的t_spec结构赋予一些初始值
{
	spec->width = -1;    //没有最小宽度
	spec->precision = -1;  //没有精度
	spec->isnull = 0;
	spec->iszero = 0;
	spec->ispos = 0;
	spec->isunsigned = 0;
	ft_bzero(spec->flags, 128);  //使得flags指针指向的128字节内容都设置为0
}


int		helper(va_list *ap, const char *restrict format)
{
	int		(*dispatch[128])(va_list *ap, t_spec *spec);  
	//这是指针，指向函数指针dispatch[0] - dispatch[127]。每一个dispatch[*]指向的是一个函数（输入是va_list和t_spec）
	//因为ascii只有128个字符，所以能显示的字符只有128个可能性。
	int		num_printed;
	int 	num;
	t_spec	spec;

	num = 0;
	spec.flags = (char *)ft_memalloc(sizeof(char) * 128);
	//把spec结构体内的字符串分配128个字符
	init_dispatch(dispatch); //把函数指针给init_dispatch(本文件上方)，此时的dispatch指针是可以通过d,s来选择用哪个函数来处理.
	while (*format) //当输入字符串存在的时候，检查这个字符串的每个字符
	{
		if (*format == '%')  //如果遇到字符%
		{
			format++; //指针后移一位
			init_spec(&spec);//指向结构体的指针给init_spec，此时的spec都是相同的，初始化
			num_printed = print_a_arg(&format, ap, dispatch, &spec);//这种过程中就把当前的参数write出来了
			//把%后的字符串作为输入放入函数
			num += num_printed;
		}
		else  //如果没遇到字符%
		{
			ft_putchar(*format); //显示该字符
			num++;  //成功显示的字符数+1
			format++; //指针后移一位
		}
	}
	free(spec.flags); //释放结构体内用到128个字符空间
	return (num);
}



//可变参数的使用方法
// 1）申明va_list 变量ap(argument point)
// 2) va_start(ap,可变参数前面一个参数名）初始化
// 3）va_end（ap) 释放调用可变参数用使用到的内存

// printf的使用方法
// printf("num1 = &d, num2, = %d", num1, num2); 显示变量num1,2的对应值
// man里面的完整函数是 int printf(const char * restrict format, ...); 返回值是成功显示的个数（不包含null)，例如"abc123\n“返回值就是7
int		ft_printf(const char *format, ...)
{
	va_list	ap;      //申明va_list 变量ap(argument point)
	int     num_chars_printed; //显示出来的字符数，不包含null。这个用于printf的返回值

	va_start(ap, format);  //va_start(ap,可变参数前面一个参数名）初始化
	num_chars_printed = helper(&ap, format); //通过helper函数获得成功打印的字符数+打印输入对应的字符。输入是argument point的地址， format指针（指向的是字符串”the num is %d"这种， 以及int 0(这个数字之后会变成成功打印的字符数)
	va_end(ap); //释放之前用到的ap内存空间，因为在整个过程中，系统是把输入的可变参数放入一个list,通过调用这个list里面的内容接入可变参数
	return (num_chars_printed);
}