/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:21:00 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:11:04 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int		*ptr;
	int		val;
	char 	c;
	char 	a;
	unsigned char b;
	char	null;
	char 	*str_null;
	short short_min;
	short short_max;
	int int_min;
	int int_max;
	long long_min;
	long long_max;
	long long llong_min;
	long long llong_max;
	float float_min;
	float float_max;
	double float_num;
	double double_num;
	double double_num2;
	long double ldouble_min;
	long double ldouble_num;

	c = 'c';
	b = 'b';
	a = 'a';
	null = 0;
	str_null = 0;
	ptr = &val;
	short_min = -32768;
	short_max = 32767;
	int_min = -2147483648;
	int_max = 2147483647;
	long_min = -2147483648;
	long_max = 2147483647;
	llong_min = -9223372036854775808;
	llong_max = 9223372036854775807;
	
	float_min = 0.000000;
	float_num = 20.1234;
	double_num = 20.123456;
	double_num2 = -20.123456;
	ldouble_min = 0.000000;
	ldouble_num = 12345678.0006;
	
	ft_printf("char:\n");
	ft_printf("char+str(%%-2c%%04c%%6s) = %-2c%04c%6s\n", c, a, "block");
	printf("char+str(%%-2c%%04c%%6s) = %-2c%04c%6s\n", c, a, "block");
	ft_printf("char(%%c->null%%c) =%c%c\n", null, c);
	printf("char(%%c->null%%c) =%c%c\n", null, c);
	ft_printf("str:\n");
	ft_printf("str(%%-5s%%5s%%08s) =%-5s%5s%08s\n", "test", "str","block");
	printf("str(%%-5s%%5s%%08s) =%-5s%5s%08s\n", "test", "str","block");
	ft_printf("str(%%s->null%%s) =%s%s\n", str_null, "str");
	printf("str(%%s->null%%s) =%s%s\n", str_null, "str");
	ft_printf("point:\n");
	ft_printf("point(%%p) =%p\n", &str_null);
	printf("point(%%p) =%p\n", &str_null);
	ft_printf("point(%%-20p%%p) =%-20p%p\n", &str_null, &str_null);
	printf("point(%%-20p%%p) =%-20p%p\n", &str_null, &str_null);
	ft_printf("point(%%-20p%%15p) =%-20p%15p\n", &str_null, &str_null);
	printf("point(%%-20p%%15p) =%-20p%15p\n", &str_null, &str_null);
	ft_printf("point(%%-20p%%0.15p) =%-20p%0.15p\n", &str_null, &str_null);
	printf("point(%%-20p%%0.15p) =%-20p%0.15p\n", &str_null, &str_null);
	ft_printf("point(%%-20p%%015p) =%-20p%015p\n", &str_null, &str_null);
	printf("point(%%-20p%%015p) =%-20p%015p\n", &str_null, &str_null);
	ft_printf("point(%%-20p%%020.10p) =%-20p%020.10p\n", &str_null, &str_null);
	printf("point(%%-20p%%020.10p) =%-20p%020.10p\n", &str_null, &str_null);
	ft_printf("decimal(%%d&%%i):\n");
	ft_printf("int max = %+- 030.30d\n", INT_MAX);
	printf("int max = %+- 030.30d\n", INT_MAX);
	ft_printf("int min = %+- 20.20d\n", INT_MIN);
	printf("int min = %+- 20.20d\n", INT_MIN);
	ft_printf("int max = % 10.10d\n", INT_MAX);
	printf("int max = % 10.10d\n", INT_MAX);
	ft_printf("hhd:signed char = %hhd, unsigned char = %hhd\n", c, b);
	printf("hhd:signed char = %hhd, unsigned char = %hhd\n", c, b);
	ft_printf("hd:short min = %hd short max = %hd\n", short_min, short_max);
	printf("hd:short min = %hd short max = %hd\n", short_min, short_max);
	ft_printf("d:int min = %d int max = %d\n", int_min, int_max);
	printf("d:int min = %d int max = %d\n", int_min, int_max);
	ft_printf("ld:long min = %ld long max(2^31 - 1) = %ld\n", long_min, long_max);
	printf("ld:long min = %ld long max(2^31 - 1) = %ld\n", long_min, long_max);
	ft_printf("lld:long long min = %lld long long max(2^63-1) = %lld\n", llong_min, llong_max);
	printf("lld:long long min = %lld long long max(2^63-1) = %lld\n", llong_min, llong_max);
	ft_printf("lld:long long min = %+- 30.20lld long long max(2^63-1) = %+- 20.20lld\n", llong_min, llong_max);
	printf("lld:long long min = %+- 30.20lld long long max(2^63-1) = %+- 20.20lld\n", llong_min, llong_max);
	ft_printf("unsigned decimal(%%u):\n");
	ft_printf("hhu:signed char = %hhu, unsigned char = %hhu\n", c, b);
	printf("hhu:signed char = %hhu, unsigned char = %hhu\n", c, b);
	ft_printf("hu:short min = %hu short max = %hu\n", short_min, short_max);
	printf("hu:short min = %hu short max = %hu\n", short_min, short_max);
	ft_printf("u:int min = %u int max = %u\n", int_min, int_max);
	printf("u:int min = %u int max = %u\n", int_min, int_max);
	ft_printf("lu:long min = %lu long max(2^31 - 1) = %lu\n", long_min, long_max);
	printf("lu:long min = %lu long max(2^31 - 1) = %lu\n", long_min, long_max);
	ft_printf("lld:long long min = %llu long long max(2^63-1) = %llu\n", llong_min, llong_max);
	printf("llu:long long min = %llu long long max(2^63-1) = %llu\n", llong_min, llong_max);
	ft_printf("hhu:signed char = %- 10.10hhu, unsigned char = %- 10.10hhu\n", c, b);
	printf("hhu:signed char = %- 10.10hhu, unsigned char = %- 10.10hhu\n", c, b);
	ft_printf("octal(%%o):\n");
	ft_printf("hho:signed char = %hho, unsigned char = %hho\n", c, b);
	printf("hho:signed char = %hho, unsigned char = %hho\n", c, b);
	ft_printf("ho:short min = %ho short max = %ho\n", short_min, short_max);
	printf("ho:short min = %ho short max = %ho\n", short_min, short_max);
	ft_printf("o:int min = %o int max = %o\n", int_min, int_max);
	printf("o:int min = %o int max = %o\n", int_min, int_max);
	ft_printf("lo:long min = %lo long max(2^31 - 1) = %lo\n", long_min, long_max);
	printf("lo:long min = %lo long max(2^31 - 1) = %lo\n", long_min, long_max);
	ft_printf("llo:long long min = %llo long long max(2^63-1) = %llo\n", llong_min, llong_max);
	printf("llo:long long min = %llo long long max(2^63-1) = %llo\n", llong_min, llong_max);
	ft_printf("o:int min = %-#10.10o int max = %#20.20o\n", int_min, int_max);
	printf("o:int min = %-#10.10o int max = %#20.20o\n", int_min, int_max);
	ft_printf("hexadecimal(%%x):\n");
	ft_printf("hhx:signed char = %hhx, unsigned char = %hhx\n", c, b);
	printf("hhx:signed char = %hhx, unsigned char = %hhx\n", c, b);
	ft_printf("hx:short min = %hx short max = %hx\n", short_min, short_max);
	printf("hx:short min = %hx short max = %hx\n", short_min, short_max);
	ft_printf("x:int min = %x int max = %x\n", int_min, int_max);
	printf("x:int min = %x int max = %x\n", int_min, int_max);
	ft_printf("lx:long min = %lx long max(2^31 - 1) = %lx\n", long_min, long_max);
	printf("lx:long min = %lx long max(2^31 - 1) = %lx\n", long_min, long_max);
	ft_printf("llx:long long min = %llx long long max(2^63-1) = %llx\n", llong_min, llong_max);
	printf("llx:long long min = %llx long long max(2^63-1) = %llx\n", llong_min, llong_max);
	ft_printf("lx:long min = %-#10.10lx long max(2^31 - 1) = %-#10.10lx\n", long_min, long_max);
	printf("lx:long min = %-#10.10lx long max(2^31 - 1) = %-#10.10lx\n", long_min, long_max);
	ft_printf("hexadecimal(%%X):\n");
	ft_printf("hhX:signed char = %hhX, unsigned char = %hhX\n", c, b);
	printf("hhX:signed char = %hhX, unsigned char = %hhX\n", c, b);
	ft_printf("hX:short min = %hX short max = %hX\n", short_min, short_max);
	printf("hX:short min = %hX short max = %hX\n", short_min, short_max);
	ft_printf("X:int min = %X int max = %X\n", int_min, int_max);
	printf("X:int min = %X int max = %X\n", int_min, int_max);
	ft_printf("lX:long min = %lX long max(2^31 - 1) = %lX\n", long_min, long_max);
	printf("lX:long min = %lX long max(2^31 - 1) = %lX\n", long_min, long_max);
	ft_printf("llX:long long min = %llX long long max(2^63-1) = %llX\n", llong_min, llong_max);
	printf("llX:long long min = %llX long long max(2^63-1) = %llX\n", llong_min, llong_max);
	ft_printf("lX:long min = %-#10.10lX long max(2^31 - 1) = %-#10.10lX\n", long_min, long_max);
	printf("lX:long min = %-#10.10lX long max(2^31 - 1) = %-#10.10lX\n", long_min, long_max);
	ft_printf("float(%%f):\n");
	ft_printf("f:float num1 = %f float num2 = %f\n", float_num, float_min);
	printf("f:float num1 = %f float num2 = %f\n", float_num, float_min);
	ft_printf("lf:double min = %lf double max = %.10lf\n", double_num, double_num2);
	printf("lf:double min = %lf double max = %.10lf\n", double_num, double_num2);
	ft_printf("Lf:long double min = %Lf long double max = %.10Lf\n", ldouble_min, ldouble_num);
	printf("Lf:long double min = %Lf long double max = %.10Lf\n", ldouble_min, ldouble_num);
	ft_printf("%hhld\n", 128); 
	printf("%hhld\n", 128); 
	ft_printf("%d\n", -128); 
	printf("%d\n", -128); 
	ft_printf("%hhld\n", 127); 
	printf("%hhld\n", 127); 
	ft_printf("%10p, %.p\n", 0, 0);
	printf("%10p, %.p\n", 0, 0);
	ft_printf("%p\n", 0);
	printf("%p\n", 0);
	ft_printf("%#.o\n", 0);
	printf("%#.o\n", 0);
	ft_printf("%o\n", LONG_MIN);
	printf("%o\n", LONG_MIN);
	ft_printf("%.4o\n", 42);
	printf("%.4o\n", 42);
	ft_printf("%.ld\n", -12);
	printf("%.ld\n", -12);
	
	return (0);
}
