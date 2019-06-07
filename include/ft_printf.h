/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 20:52:12 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/06 21:36:01 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

typedef	struct		s_spec  //这个结构体用来存储一些值,有一个字符串和一些int来判断一些**的一些特性
{
	char			*flags;   //存放flags字符
	int				isnull;   //1的话，表示指向机器码0。默认是0
	int				iszero;   //1的话，表示所指的数字int是0
	int				width;   //存放最小显示宽度数字
	int				precision;  //存放显示精度数字
	int				ispos;  //1是正数，0的话是负数
	int				isunsigned; //1的话是unsigned,0是signed
}					t_spec;

typedef struct		s_width_d   //用与最小宽度处理
{
	int				pad_len;  //需要填充的宽度
	int				len;      //输入的可显示的字符长度（已经处理过精度，不够的已填满）
	char			c;
	char			*new;    //新字符串地址
	char			*padding; //填入的字符串空间
}					t_width_d;

int					ft_printf(const char *format, ...);
int					conv_s(va_list *ap, t_spec *spec);
int					conv_c(va_list *ap, t_spec *spec);
int					conv_p(va_list *ap, t_spec *spec);
//for char+str
int					print_a_arg(const char *restrict *format, \
					va_list *ap, int (*dispatch[])(), t_spec *spec);
int					get_len_modifier(const char *restrict *format, char *flags);
int					conv_single(t_spec *spec, char c);
void				width_s(char **str, t_spec *spec);
char				*width_s_2(int pad_len, char *padding, char c);
char				get_conv_spec(const char *restrict *format, char *flags);
//for point
void				itoa_hex(unsigned long vp_num, char **str, t_spec *spec);
void				width_p(char **str, t_spec *spec);
void				width_p_2(char **str, t_width_d v);
void				prefix_0x(char **str);
void				precision_p(char **str, t_spec *spec);
//for decimal(%d)
int					conv_d(va_list *ap, t_spec *spec);
long long			len_mod(va_list *ap, t_spec *spec);
void				prefix_octal(char **str, t_spec *spec);
void				prefix_sign(char **str, t_spec *spec);
void				itoa_d(long long num, char **str, t_spec *spec);
void				precision_d(char **str, t_spec *spec);
void				width_d(char **str, t_spec *spec);
void				width_d_2(char **str, t_spec *spec, t_width_d v);
//for unsigned decimal(%u)
int			conv_u(va_list *ap, t_spec *spec);
unsigned long long	lenmod_unsigned(va_list *ap, t_spec *spec);
void		itoa_u(unsigned long long num, char **str);
int			itoa_u_len(unsigned long long num);
void		itoa_u_str(unsigned long long num, char **str, int len);
//for octal
int			conv_o(va_list *ap, t_spec *spec);
void		itoa_octal(unsigned long long num, char **str);
//for hexadecimal
int			conv_x(va_list *ap, t_spec *spec);
//for float
int			conv_f(va_list *ap, t_spec *spec);
void		lftos(long double num, char **str, t_spec *spec);
void		ftos(double num, char **str, t_spec *spec);
long		power(int base, int exp);
int			fractional(char **str, long long fract, t_spec *spec);
void		itoa_snip(char **str, int i, long long val);
void		dtoa(double num, char **str, t_spec *spec);
int			d_len(long val);
void		prefix(char *pre, char **str);




#endif